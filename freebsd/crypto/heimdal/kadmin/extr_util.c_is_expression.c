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
 int /*<<< orphan*/ * strchr (char*,char const) ; 

__attribute__((used)) static int
is_expression(const char *string)
{
    const char *p;
    int quote = 0;

    for(p = string; *p; p++) {
	if(quote) {
	    quote = 0;
	    continue;
	}
	if(*p == '\\')
	    quote++;
	else if(strchr("[]*?", *p) != NULL)
	    return 1;
    }
    return 0;
}