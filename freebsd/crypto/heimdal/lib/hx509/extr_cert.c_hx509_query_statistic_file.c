#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_context ;
struct TYPE_3__ {scalar_t__ querystat; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ strdup (char const*) ; 

void
hx509_query_statistic_file(hx509_context context, const char *fn)
{
    if (context->querystat)
	free(context->querystat);
    context->querystat = strdup(fn);
}