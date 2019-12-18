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
struct proto_softc {int dummy; } ;
struct proto_busdma {int /*<<< orphan*/  sxlck; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PROTO_BUSDMA ; 
 int /*<<< orphan*/  free (struct proto_busdma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_busdma_cleanup (struct proto_softc*,struct proto_busdma*) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

int
proto_busdma_detach(struct proto_softc *sc, struct proto_busdma *busdma)
{

	proto_busdma_cleanup(sc, busdma);
	sx_destroy(&busdma->sxlck);
	free(busdma, M_PROTO_BUSDMA);
	return (0);
}