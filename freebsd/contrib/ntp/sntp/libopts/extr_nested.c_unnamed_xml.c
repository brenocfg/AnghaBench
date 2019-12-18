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
 char* strchr (char const*,char) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static char const *
unnamed_xml(char const * txt)
{
    switch (*txt) {
    default:
        txt = NULL;
        break;

    case '!':
        txt = strstr(txt, "-->");
        if (txt != NULL)
            txt += 3;
        break;

    case '?':
        txt = strchr(txt, '>');
        if (txt != NULL)
            txt++;
        break;
    }
    return txt;
}