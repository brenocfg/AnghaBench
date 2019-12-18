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
struct srch {int s_value; char const* s_name; } ;

/* Variables and functions */
 int nsrchn ; 
 struct srch* srchn ; 

__attribute__((used)) static const char *
isrchx(int n)
{
    struct srch *sp, *sp2;

    for (sp = srchn, sp2 = srchn + nsrchn; sp < sp2; sp++)
	if (sp->s_value == n)
	    return (sp->s_name);
    return ("");
}