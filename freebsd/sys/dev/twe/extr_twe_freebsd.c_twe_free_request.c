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
struct twe_softc {int /*<<< orphan*/  twe_buffer_dmat; } ;
struct twe_request {int /*<<< orphan*/  tr_dmamap; struct twe_softc* tr_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_MALLOC_CLASS ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (struct twe_request*,int /*<<< orphan*/ ) ; 

void
twe_free_request(struct twe_request *tr) 
{
    struct twe_softc	*sc = tr->tr_sc;
    
    debug_called(4);

    bus_dmamap_destroy(sc->twe_buffer_dmat, tr->tr_dmamap);
    free(tr, TWE_MALLOC_CLASS);
}