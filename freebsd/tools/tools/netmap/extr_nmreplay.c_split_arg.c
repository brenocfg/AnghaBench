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
 int /*<<< orphan*/  ND (char*,int,...) ; 
 int /*<<< orphan*/  NED (char*,int,char*) ; 
 char** calloc (int,int) ; 
 scalar_t__ strchr (char*,char const) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char **
split_arg(const char *src, int *_ac)
{
    char *my = NULL, **av = NULL, *seps = " \t\r\n,";
    int l, i, ac; /* number of entries */

    if (!src)
	return NULL;
    l = strlen(src);
    /* in the first pass we count fields, in the second pass
     * we allocate the av[] array and a copy of the string
     * and fill av[]. av[ac] = NULL, av[ac+1]
     */
    for (;;) {
	i = ac = 0;
	ND("start pass %d: <%s>", av ? 1 : 0, my);
	while (i < l) {
	    /* trim leading separator */
	    while (i <l && strchr(seps, src[i]))
		i++;
	    if (i >= l)
		break;
	    ND("   pass %d arg %d: <%s>", av ? 1 : 0, ac, src+i);
	    if (av) /* in the second pass, set the result */
		av[ac] = my+i;
	    ac++;
	    /* skip string */
	    while (i <l && !strchr(seps, src[i])) i++;
	    if (av)
		my[i] = '\0'; /* write marker */
	}
	if (!av) { /* end of first pass */
	    ND("ac is %d", ac);
	    av = calloc(1, (l+1) + (ac + 2)*sizeof(char *));
	    my = (char *)&(av[ac+2]);
	    strcpy(my, src);
	} else {
	    break;
	}
    }
    for (i = 0; i < ac; i++) {
	NED("%d: <%s>", i, av[i]);
    }
    av[i++] = NULL;
    av[i++] = my;
    *_ac = ac;
    return av;
}