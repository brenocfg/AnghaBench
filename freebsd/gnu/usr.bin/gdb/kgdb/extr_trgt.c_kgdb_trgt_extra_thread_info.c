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
struct thread_info {int /*<<< orphan*/  ptid; } ;

/* Variables and functions */
 char* kgdb_thr_extra_thread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_get_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
kgdb_trgt_extra_thread_info(struct thread_info *ti)
{

	return (kgdb_thr_extra_thread_info(ptid_get_pid(ti->ptid)));
}