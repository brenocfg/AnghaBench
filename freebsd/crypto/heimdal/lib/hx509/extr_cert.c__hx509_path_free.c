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
struct TYPE_3__ {unsigned int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ hx509_path ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ ) ; 

void
_hx509_path_free(hx509_path *path)
{
    unsigned i;

    for (i = 0; i < path->len; i++)
	hx509_cert_free(path->val[i]);
    free(path->val);
    path->val = NULL;
    path->len = 0;
}