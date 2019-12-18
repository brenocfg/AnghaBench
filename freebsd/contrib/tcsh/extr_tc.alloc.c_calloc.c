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
typedef  int /*<<< orphan*/  memalign_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t volatile) ; 
 char* xmalloc (size_t) ; 

memalign_t
calloc(size_t i, size_t j)
{
#ifndef lint
    char *cp;
    volatile size_t k;

    i *= j;
    cp = xmalloc(i);
    /* Stop gcc 5.x from optimizing malloc+memset = calloc */
    k = i;
    memset(cp, 0, k);

    return ((memalign_t) cp);
#else
    if (i && j)
	return ((memalign_t) 0);
    else
	return ((memalign_t) 0);
#endif
}