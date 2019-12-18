#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct thread {int dummy; } ;
struct TYPE_5__ {scalar_t__ dh_size; scalar_t__ dh_sigstate; int /*<<< orphan*/  dh_type; int /*<<< orphan*/  dh_waitlisthead; } ;
struct TYPE_6__ {TYPE_1__ no_dh; int /*<<< orphan*/  no_obj; } ;
typedef  TYPE_2__ nt_objref ;
typedef  int /*<<< orphan*/  ndis_status ;
typedef  int /*<<< orphan*/  ndis_handle ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_TYPE_THREAD ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntoskrnl_reflist ; 

__attribute__((used)) static ndis_status
ObReferenceObjectByHandle(ndis_handle handle, uint32_t reqaccess, void *otype,
	uint8_t accessmode, void **object, void **handleinfo)
{
	nt_objref		*nr;

	nr = malloc(sizeof(nt_objref), M_DEVBUF, M_NOWAIT|M_ZERO);
	if (nr == NULL)
		return (STATUS_INSUFFICIENT_RESOURCES);

	InitializeListHead((&nr->no_dh.dh_waitlisthead));
	nr->no_obj = handle;
	nr->no_dh.dh_type = DISP_TYPE_THREAD;
	nr->no_dh.dh_sigstate = 0;
	nr->no_dh.dh_size = (uint8_t)(sizeof(struct thread) /
	    sizeof(uint32_t));
	TAILQ_INSERT_TAIL(&ntoskrnl_reflist, nr, link);
	*object = nr;

	return (STATUS_SUCCESS);
}