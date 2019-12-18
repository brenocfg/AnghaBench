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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int parse_time_string (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
parse_time_string_alloc (time_t **t, const char *s)
{
    time_t tmp;
    int ret;

    *t = NULL;
    ret = parse_time_string (&tmp, s);
    if (ret == 1) {
	*t = malloc (sizeof (**t));
	if (*t == NULL)
	    krb5_errx (context, 1, "malloc: out of memory");
	**t = tmp;
    }
    return ret;
}