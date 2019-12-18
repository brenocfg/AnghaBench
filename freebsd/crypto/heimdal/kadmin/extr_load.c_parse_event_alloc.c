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
typedef  int /*<<< orphan*/  Event ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int parse_event (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
parse_event_alloc (Event **ev, char *s)
{
    Event tmp;
    int ret;

    *ev = NULL;
    ret = parse_event (&tmp, s);
    if (ret == 1) {
	*ev = malloc (sizeof (**ev));
	if (*ev == NULL)
	    krb5_errx (context, 1, "malloc: out of memory");
	**ev = tmp;
    }
    return ret;
}