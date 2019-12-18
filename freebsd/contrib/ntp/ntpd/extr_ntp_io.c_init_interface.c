#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phase; void* bfd; void* fd; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 void* INVALID_SOCKET ; 
 int /*<<< orphan*/  ZERO (TYPE_1__) ; 
 int /*<<< orphan*/  sys_interphase ; 

__attribute__((used)) static void
init_interface(
	endpt *ep
	)
{
	ZERO(*ep);
	ep->fd = INVALID_SOCKET;
	ep->bfd = INVALID_SOCKET;
	ep->phase = sys_interphase;
}