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

/* Variables and functions */
 int /*<<< orphan*/  UNKNOWN_ENTRY_POINT ; 
 int /*<<< orphan*/  afs_entry_point ; 
 int k_hasafs () ; 

int
k_hasafs_recheck(void)
{
    afs_entry_point = UNKNOWN_ENTRY_POINT;
    return k_hasafs();
}