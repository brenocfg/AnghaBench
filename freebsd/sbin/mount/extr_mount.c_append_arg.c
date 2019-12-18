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
struct cpa {int c; int sz; char** a; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 char** realloc (char**,int) ; 

__attribute__((used)) static void
append_arg(struct cpa *sa, char *arg)
{
	if (sa->c + 1 == sa->sz) {
		sa->sz = sa->sz == 0 ? 8 : sa->sz * 2;
		sa->a = realloc(sa->a, sizeof(*sa->a) * sa->sz);
		if (sa->a == NULL)
			errx(1, "realloc failed");
	}
	sa->a[++sa->c] = arg;
}