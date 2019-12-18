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
 int db_copy_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pacct_db ; 
 int /*<<< orphan*/  pdb_file ; 
 int /*<<< orphan*/  v1_to_v2 ; 

int
pacct_init(void)
{
	return (db_copy_in(&pacct_db, pdb_file, "process accounting",
	    NULL, v1_to_v2));
}