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
 char* basename (char*) ; 
 int do_fstat (int,char**) ; 
 int do_fuser (int,char**) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
main(int argc, char *argv[])
{
	char *p;

	p = basename(argv[0]);
	if (p == NULL)
		err(1, "basename(%s)", argv[0]);
	if (!strcmp(p, "fuser"))
		return (do_fuser(argc, argv));
	else
		return (do_fstat(argc, argv));
}