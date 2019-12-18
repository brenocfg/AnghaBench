#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proc_handle {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pr_mapname; } ;
typedef  TYPE_1__ prmap_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ctf_open (int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* proc_name2map (struct proc_handle*,char const*) ; 

ctf_file_t *
proc_name2ctf(struct proc_handle *p, const char *name)
{
#ifndef NO_CTF
	ctf_file_t *ctf;
	prmap_t *map;
	int error;

	if ((map = proc_name2map(p, name)) == NULL)
		return (NULL);

	ctf = ctf_open(map->pr_mapname, &error);
	return (ctf);
#else
	(void)p;
	(void)name;
	return (NULL);
#endif
}