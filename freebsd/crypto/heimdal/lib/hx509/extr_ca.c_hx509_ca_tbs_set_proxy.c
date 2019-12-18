#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_2__* hx509_ca_tbs ;
struct TYPE_4__ {int proxy; } ;
struct TYPE_5__ {int pathLenConstraint; TYPE_1__ flags; } ;

/* Variables and functions */

int
hx509_ca_tbs_set_proxy(hx509_context context,
		       hx509_ca_tbs tbs,
		       int pathLenConstraint)
{
    tbs->flags.proxy = 1;
    tbs->pathLenConstraint = pathLenConstraint;
    return 0;
}