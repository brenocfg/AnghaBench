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
typedef  int /*<<< orphan*/  z ;
typedef  scalar_t__ tOptionLoadMode ;
typedef  int /*<<< orphan*/  fmt ;

/* Variables and functions */
 char* AGALOC (size_t,char*) ; 
 int /*<<< orphan*/  AGFREE (char*) ; 
 char NUL ; 
 scalar_t__ OPTION_LOAD_UNCOOKED ; 
 char* SPN_WHITESPACE_BACK (char*,char*) ; 
 scalar_t__ sprintf (char*,char const*,char const*) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *
trim_xml_text(char * intxt, char const * pznm, tOptionLoadMode mode)
{
    static char const fmt[] = "</%s>";
    size_t len = strlen(pznm) + sizeof(fmt) - 2 /* for %s */;
    char * etext;

    {
        char z[64], *pz = z;
        if (len >= sizeof(z))
            pz = AGALOC(len, "scan name");

        len = (size_t)sprintf(pz, fmt, pznm);
        *intxt = ' ';
        etext = strstr(intxt, pz);
        if (pz != z) AGFREE(pz);
    }

    if (etext == NULL)
        return etext;

    {
        char * result = etext + len;

        if (mode != OPTION_LOAD_UNCOOKED)
            etext = SPN_WHITESPACE_BACK(intxt, etext);

        *etext = NUL;
        return result;
    }
}