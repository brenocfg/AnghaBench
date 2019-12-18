#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  adapter_dmatag; } ;
typedef  TYPE_1__ ips_softc_t ;
struct TYPE_8__ {int /*<<< orphan*/  data_dmatag; int /*<<< orphan*/  data_dmamap; int /*<<< orphan*/  data_buffer; int /*<<< orphan*/  callback; TYPE_1__* sc; } ;
typedef  TYPE_2__ ips_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IPS_DRIVE_INFO_LEN ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_drive_info_callback ; 
 int /*<<< orphan*/  ips_insert_free_cmd (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ips_wakeup_callback ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int ips_send_drive_info_cmd(ips_command_t *command)
{
	int error = 0;
	ips_softc_t *sc = command->sc;

	if (bus_dma_tag_create(	/* parent    */	sc->adapter_dmatag,
				/* alignemnt */	1,
				/* boundary  */	0,
				/* lowaddr   */	BUS_SPACE_MAXADDR_32BIT,
				/* highaddr  */	BUS_SPACE_MAXADDR,
				/* filter    */	NULL,
				/* filterarg */	NULL,
				/* maxsize   */	IPS_DRIVE_INFO_LEN,
				/* numsegs   */	1,
				/* maxsegsize*/	IPS_DRIVE_INFO_LEN,
				/* flags     */	0,
				/* lockfunc  */ NULL,
				/* lockarg   */ NULL,
				&command->data_dmatag) != 0) {
                printf("ips: can't alloc dma tag for drive status\n");
		error = ENOMEM;
		goto exit;
        }
	if(bus_dmamem_alloc(command->data_dmatag, &command->data_buffer, 
	   		    BUS_DMA_NOWAIT, &command->data_dmamap)){
		error = ENOMEM;
		goto exit;
	}
	command->callback = ips_wakeup_callback;
	error = bus_dmamap_load(command->data_dmatag, command->data_dmamap, 
				command->data_buffer,IPS_DRIVE_INFO_LEN, 
				ips_drive_info_callback, command,
				BUS_DMA_NOWAIT);
	if (error == 0)
		bus_dmamap_unload(command->data_dmatag, command->data_dmamap);

exit:
	/* I suppose I should clean up my memory allocations */
	bus_dmamem_free(command->data_dmatag, command->data_buffer, 
			command->data_dmamap);
	bus_dma_tag_destroy(command->data_dmatag);
	ips_insert_free_cmd(sc, command);
	return error;

}