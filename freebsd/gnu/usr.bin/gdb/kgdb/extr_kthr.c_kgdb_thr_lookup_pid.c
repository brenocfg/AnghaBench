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
struct kthr {int pid; struct kthr* next; } ;

/* Variables and functions */
 struct kthr* first ; 

struct kthr *
kgdb_thr_lookup_pid(int pid)
{
	struct kthr *kt;

	kt = first;
	while (kt != NULL && kt->pid != pid)
		kt = kt->next;
	return (kt);
}