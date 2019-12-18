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
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 unsigned int* malloc (int) ; 
 int parse_integer (unsigned int*,char const*) ; 

__attribute__((used)) static int
parse_integer_alloc (unsigned int **u, const char *s)
{
    unsigned int tmp;
    int ret;

    *u = NULL;
    ret = parse_integer (&tmp, s);
    if (ret == 1) {
	*u = malloc (sizeof (**u));
	if (*u == NULL)
	    krb5_errx (context, 1, "malloc: out of memory");
	**u = tmp;
    }
    return ret;
}