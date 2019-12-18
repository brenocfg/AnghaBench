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
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static char *
skip_next(char *p)
{
    while(*p && !isspace((unsigned char)*p))
	p++;
    *p++ = 0;
    while(*p && isspace((unsigned char)*p))
	p++;
    return p;
}