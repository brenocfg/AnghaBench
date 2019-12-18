#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct aac_softc {scalar_t__ total_fibs; int aac_max_fibs_alloc; scalar_t__ aac_max_fibs; int aac_max_fib_size; int /*<<< orphan*/  aac_fib_dmat; int /*<<< orphan*/  aac_io_lock; int /*<<< orphan*/  aac_fibmap_tqh; int /*<<< orphan*/  aac_buffer_dmat; struct aac_command* aac_commands; int /*<<< orphan*/  aac_dev; } ;
struct aac_fibmap {int /*<<< orphan*/  aac_fibmap; scalar_t__ aac_fibs; struct aac_command* aac_commands; } ;
struct aac_fib {int dummy; } ;
struct aac_command {int /*<<< orphan*/  cm_datamap; struct aac_command* cm_index; scalar_t__ cm_fibphys; struct aac_fib* cm_fib; struct aac_softc* cm_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int ENOMEM ; 
 char* HBA_FLAGS_DBG_COMM_B ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  M_AACBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct aac_fibmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_map_command_helper ; 
 int /*<<< orphan*/  aac_release_command (struct aac_command*) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fm_link ; 
 int /*<<< orphan*/  free (struct aac_fibmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*,...) ; 
 struct aac_fibmap* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aac_alloc_commands(struct aac_softc *sc)
{
	struct aac_command *cm;
	struct aac_fibmap *fm;
	uint64_t fibphys;
	int i, error;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	if (sc->total_fibs + sc->aac_max_fibs_alloc > sc->aac_max_fibs)
		return (ENOMEM);

	fm = malloc(sizeof(struct aac_fibmap), M_AACBUF, M_NOWAIT|M_ZERO);
	if (fm == NULL)
		return (ENOMEM);

	/* allocate the FIBs in DMAable memory and load them */
	if (bus_dmamem_alloc(sc->aac_fib_dmat, (void **)&fm->aac_fibs,
			     BUS_DMA_NOWAIT, &fm->aac_fibmap)) {
		device_printf(sc->aac_dev,
			      "Not enough contiguous memory available.\n");
		free(fm, M_AACBUF);
		return (ENOMEM);
	}

	/* Ignore errors since this doesn't bounce */
	(void)bus_dmamap_load(sc->aac_fib_dmat, fm->aac_fibmap, fm->aac_fibs,
			      sc->aac_max_fibs_alloc * sc->aac_max_fib_size,
			      aac_map_command_helper, &fibphys, 0);

	/* initialize constant fields in the command structure */
	bzero(fm->aac_fibs, sc->aac_max_fibs_alloc * sc->aac_max_fib_size);
	for (i = 0; i < sc->aac_max_fibs_alloc; i++) {
		cm = sc->aac_commands + sc->total_fibs;
		fm->aac_commands = cm;
		cm->cm_sc = sc;
		cm->cm_fib = (struct aac_fib *)
			((u_int8_t *)fm->aac_fibs + i*sc->aac_max_fib_size);
		cm->cm_fibphys = fibphys + i*sc->aac_max_fib_size;
		cm->cm_index = sc->total_fibs;

		if ((error = bus_dmamap_create(sc->aac_buffer_dmat, 0,
					       &cm->cm_datamap)) != 0)
			break;
		mtx_lock(&sc->aac_io_lock);
		aac_release_command(cm);
		sc->total_fibs++;
		mtx_unlock(&sc->aac_io_lock);
	}

	if (i > 0) {
		mtx_lock(&sc->aac_io_lock);
		TAILQ_INSERT_TAIL(&sc->aac_fibmap_tqh, fm, fm_link);
		fwprintf(sc, HBA_FLAGS_DBG_COMM_B, "total_fibs= %d\n", sc->total_fibs);
		mtx_unlock(&sc->aac_io_lock);
		return (0);
	}

	bus_dmamap_unload(sc->aac_fib_dmat, fm->aac_fibmap);
	bus_dmamem_free(sc->aac_fib_dmat, fm->aac_fibs, fm->aac_fibmap);
	free(fm, M_AACBUF);
	return (ENOMEM);
}