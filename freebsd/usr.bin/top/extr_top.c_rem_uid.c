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
struct TYPE_2__ {int* uid; } ;

/* Variables and functions */
 size_t TOP_MAX_UIDS ; 
 TYPE_1__ ps ; 

__attribute__((used)) static void
rem_uid(int uid)
{
    size_t i = 0;
    size_t where = TOP_MAX_UIDS;

    /* Look for the user to remove - no problem if it's not there */
    for (; i < TOP_MAX_UIDS; ++i)
    {
	if (ps.uid[i] == -1)
	    break;
	if (ps.uid[i] == uid)
	    where = i;
    }

    /* Make sure we don't leave a hole in the middle */
    if (where != TOP_MAX_UIDS)
    {
	ps.uid[where] = ps.uid[i-1];
	ps.uid[i-1] = -1;
    }
}