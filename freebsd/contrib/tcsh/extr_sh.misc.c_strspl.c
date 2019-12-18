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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 char* xmalloc (size_t) ; 

char   *
strspl(const char *cp, const char *dp)
{
    char   *ep;
    size_t cl, dl;

    if (!cp)
	cp = "";
    if (!dp)
	dp = "";
    cl = strlen(cp);
    dl = strlen(dp);
    ep = xmalloc((cl + dl + 1) * sizeof(char));
    memcpy(ep, cp, cl);
    memcpy(ep + cl, dp, dl + 1);
    return (ep);
}