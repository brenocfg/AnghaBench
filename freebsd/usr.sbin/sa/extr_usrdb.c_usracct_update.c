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
struct TYPE_4__ {int /*<<< orphan*/  compare; } ;
typedef  TYPE_1__ BTREEINFO ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int db_copy_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  uid_compare ; 
 int /*<<< orphan*/  usracct_db ; 
 int /*<<< orphan*/  usrdb_file ; 

int
usracct_update(void)
{
	BTREEINFO bti;

	bzero(&bti, sizeof bti);
	bti.compare = uid_compare;

	return (db_copy_out(usracct_db, usrdb_file, "user accounting",
	    &bti));
}