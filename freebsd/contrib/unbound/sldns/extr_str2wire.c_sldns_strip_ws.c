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
 char* strchr (char*,int /*<<< orphan*/ ) ; 

char *
sldns_strip_ws(char *line)
{
        char *s = line, *e;

        for (s = line; *s && isspace((unsigned char)*s); s++)
                ;
        for (e = strchr(s, 0); e > s+2 && isspace((unsigned char)e[-1]) && e[-2] != '\\'; e--)
                ;
        *e = 0;
        return s;
}