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
typedef  TYPE_1__* hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
struct TYPE_3__ {int /*<<< orphan*/  certs; } ;

/* Variables and functions */
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
hx509_lock_reset_certs(hx509_context context, hx509_lock lock)
{
    hx509_certs certs = lock->certs;
    int ret;

    ret = hx509_certs_init(context,
			   "MEMORY:locks-internal",
			   0,
			   NULL,
			   &lock->certs);
    if (ret == 0)
	hx509_certs_free(&certs);
    else
	lock->certs = certs;
}