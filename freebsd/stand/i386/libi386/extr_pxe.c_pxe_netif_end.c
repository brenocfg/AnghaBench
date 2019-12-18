#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Status; } ;
typedef  TYPE_1__ t_PXENV_UNDI_CLOSE ;
struct netif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PXENV_UNDI_CLOSE ; 
 TYPE_1__* bio_alloc (int) ; 
 int /*<<< orphan*/  bio_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  pxe_call (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
pxe_netif_end(struct netif *nif)
{
	t_PXENV_UNDI_CLOSE *undi_close_p;

	undi_close_p = bio_alloc(sizeof(*undi_close_p));
	if (undi_close_p != NULL) {
		bzero(undi_close_p, sizeof(*undi_close_p));
		pxe_call(PXENV_UNDI_CLOSE, undi_close_p);
		if (undi_close_p->Status != 0)
			printf("undi close failed: %x\n", undi_close_p->Status);
		bio_free(undi_close_p, sizeof(*undi_close_p));
	}
}