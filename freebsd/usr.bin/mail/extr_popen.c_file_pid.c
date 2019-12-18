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
struct fp {int /*<<< orphan*/  pid; int /*<<< orphan*/ * fp; struct fp* link; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 struct fp* fp_head ; 

pid_t
file_pid(FILE *fp)
{
	struct fp *p;

	for (p = fp_head; p != NULL; p = p->link)
		if (p->fp == fp)
			return (p->pid);
	errx(1, "Invalid file pointer");
	/*NOTREACHED*/
}