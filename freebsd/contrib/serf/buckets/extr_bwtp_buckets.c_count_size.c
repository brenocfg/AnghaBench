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
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int count_size(void *baton, const char *key, const char *value)
{
    apr_size_t *c = baton;
    /* TODO Deal with folding.  Yikes. */

    /* Add in ": " and CRLF - so an extra four bytes. */
    *c += strlen(key) + strlen(value) + 4;

    return 0;
}