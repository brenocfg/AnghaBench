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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/ * kgdb_thr_lookup_tid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_get_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kgdb_trgt_thread_alive(ptid_t ptid)
{
	return (kgdb_thr_lookup_tid(ptid_get_pid(ptid)) != NULL);
}