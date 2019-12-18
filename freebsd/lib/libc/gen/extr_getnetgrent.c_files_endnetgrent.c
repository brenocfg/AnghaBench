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
typedef  int /*<<< orphan*/  va_list ;
struct netgr_state {int dummy; } ;

/* Variables and functions */
 int NS_SUCCESS ; 
 int NS_UNAVAIL ; 
 int /*<<< orphan*/  netgr_endstate (struct netgr_state*) ; 
 scalar_t__ netgr_getstate (struct netgr_state**) ; 

__attribute__((used)) static int
files_endnetgrent(void *retval, void *mdata, va_list ap)
{
	struct netgr_state *st;

	if (netgr_getstate(&st) != 0)
		return (NS_UNAVAIL);
	netgr_endstate(st);
	return (NS_SUCCESS);
}