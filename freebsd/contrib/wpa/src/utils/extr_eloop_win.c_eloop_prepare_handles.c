#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_handles; int reader_count; int event_count; int /*<<< orphan*/ * handles; } ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 TYPE_1__ eloop ; 
 int /*<<< orphan*/ * os_realloc_array (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int eloop_prepare_handles(void)
{
	HANDLE *n;

	if (eloop.num_handles > eloop.reader_count + eloop.event_count + 8)
		return 0;
	n = os_realloc_array(eloop.handles, eloop.num_handles * 2,
			     sizeof(eloop.handles[0]));
	if (n == NULL)
		return -1;
	eloop.handles = n;
	eloop.num_handles *= 2;
	return 0;
}