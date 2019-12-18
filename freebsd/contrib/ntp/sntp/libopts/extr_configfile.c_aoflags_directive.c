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
typedef  int /*<<< orphan*/  tOptions ;

/* Variables and functions */
 char* AGALOC (size_t,char*) ; 
 int /*<<< orphan*/  AGFREE (char*) ; 
 char NUL ; 
 char* SPN_WHITESPACE_CHARS (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  set_usage_flags (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char *
aoflags_directive(tOptions * opts, char * txt)
{
    char * pz;

    pz = SPN_WHITESPACE_CHARS(txt+1);
    txt = strchr(pz, '>');
    if (txt != NULL) {

        size_t len  = (unsigned)(txt - pz);
        char * ftxt = AGALOC(len + 1, "aoflags");

        memcpy(ftxt, pz, len);
        ftxt[len] = NUL;
        set_usage_flags(opts, ftxt);
        AGFREE(ftxt);

        txt++;
    }

    return txt;
}