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
struct fp {struct fp* link; int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 struct fp* fp_head ; 
 int /*<<< orphan*/  free (struct fp*) ; 

void
unregister_file(FILE *fp)
{
	struct fp **pp, *p;

	for (pp = &fp_head; (p = *pp) != NULL; pp = &p->link)
		if (p->fp == fp) {
			*pp = p->link;
			(void)free(p);
			return;
		}
	errx(1, "Invalid file pointer");
	/*NOTREACHED*/
}