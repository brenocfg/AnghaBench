#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* pzPROGNAME; } ;
typedef  TYPE_1__ tOptions ;

/* Variables and functions */
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* strchr (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *
handle_section(tOptions * opts, char * txt)
{
    size_t len = strlen(opts->pzPROGNAME);
    if (   (strncmp(txt+1, opts->pzPROGNAME, len) == 0)
        && (txt[len+1] == ']'))
        return strchr(txt + len + 2, NL);

    if (len > 16)
        return NULL;

    {
        char z[24];
        sprintf(z, "[%s]", opts->pzPROGNAME);
        txt = strstr(txt, z);
    }

    if (txt != NULL)
        txt = strchr(txt, NL);
    return txt;
}