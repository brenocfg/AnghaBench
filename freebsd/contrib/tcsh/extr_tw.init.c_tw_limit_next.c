#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int Strbuf ;
struct TYPE_2__ {char* limname; } ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_append1 (int*,char const) ; 
 int /*<<< orphan*/  USE (int*) ; 
 TYPE_1__* tw_limit ; 

int
tw_limit_next(struct Strbuf *res, struct Strbuf *dir, int *flags)
{
    USE(dir);
    USE(flags);
#ifndef HAVENOLIMIT
    if (tw_limit && tw_limit->limname) {
	const char *ptr;

	for (ptr = tw_limit->limname; *ptr != '\0'; ptr++)
	    Strbuf_append1(res, *ptr);
	tw_limit++;
	return 1;
    }
#endif /* ! HAVENOLIMIT */
    return 0;
}