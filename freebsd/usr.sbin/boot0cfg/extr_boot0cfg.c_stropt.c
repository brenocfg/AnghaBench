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
struct TYPE_2__ {scalar_t__ def; int /*<<< orphan*/  tok; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int nopt ; 
 TYPE_1__* opttbl ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
stropt(const char *arg, int *xa, int *xo)
{
    const char *q;
    char *s, *s1;
    int inv, i, x;

    if (!(s = strdup(arg)))
        err(1, NULL);
    for (s1 = s; (q = strtok(s1, ",")); s1 = NULL) {
        if ((inv = !strncmp(q, "no", 2)))
            q += 2;
        for (i = 0; i < nopt; i++)
            if (!strcmp(q, opttbl[i].tok))
                break;
        if (i == nopt)
            errx(1, "%s: Unknown -o option", q);
        if (opttbl[i].def)
            inv ^= 1;
        x = 1 << (7 - i);
        if (inv)
            *xa &= ~x;
        else
            *xo |= x;
    }
    free(s);
}