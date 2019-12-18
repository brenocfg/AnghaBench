#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * xo_leading_xpath; } ;
typedef  TYPE_1__ xo_handle_t ;

/* Variables and functions */
 TYPE_1__* xo_default (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xo_strndup (char const*,int) ; 

void
xo_set_leading_xpath (xo_handle_t *xop, const char *path)
{
    xop = xo_default(xop);

    if (xop->xo_leading_xpath) {
	xo_free(xop->xo_leading_xpath);
	xop->xo_leading_xpath = NULL;
    }

    if (path == NULL)
	return;

    xop->xo_leading_xpath = xo_strndup(path, -1);
}