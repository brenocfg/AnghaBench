#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ Status; } ;
typedef  TYPE_1__ t_PXENV_UNLOAD_STACK ;
typedef  TYPE_1__ t_PXENV_UNDI_SHUTDOWN ;

/* Variables and functions */
 int /*<<< orphan*/  PXENV_UNDI_SHUTDOWN ; 
 int /*<<< orphan*/  PXENV_UNLOAD_STACK ; 
 TYPE_1__* bio_alloc (int) ; 
 int /*<<< orphan*/  bio_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  pxe_call (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ pxe_debug ; 

__attribute__((used)) static void
pxe_cleanup(void)
{
	t_PXENV_UNLOAD_STACK *unload_stack_p;
	t_PXENV_UNDI_SHUTDOWN *undi_shutdown_p;

	if (pxe_call == NULL)
		return;

	undi_shutdown_p = bio_alloc(sizeof(*undi_shutdown_p));
	if (undi_shutdown_p != NULL) {
		bzero(undi_shutdown_p, sizeof(*undi_shutdown_p));
		pxe_call(PXENV_UNDI_SHUTDOWN, undi_shutdown_p);

#ifdef PXE_DEBUG
		if (pxe_debug && undi_shutdown_p->Status != 0)
			printf("pxe_cleanup: UNDI_SHUTDOWN failed %x\n",
			    undi_shutdown_p->Status);
#endif
		bio_free(undi_shutdown_p, sizeof(*undi_shutdown_p));
	}

	unload_stack_p = bio_alloc(sizeof(*unload_stack_p));
	if (unload_stack_p != NULL) {
		bzero(unload_stack_p, sizeof(*unload_stack_p));
		pxe_call(PXENV_UNLOAD_STACK, unload_stack_p);

#ifdef PXE_DEBUG
		if (pxe_debug && unload_stack_p->Status != 0)
			printf("pxe_cleanup: UNLOAD_STACK failed %x\n",
			    unload_stack_p->Status);
#endif
		bio_free(unload_stack_p, sizeof(*unload_stack_p));
	}
}