#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_cursor ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_2__* hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;
struct TYPE_6__ {int /*<<< orphan*/  ops_data; TYPE_1__* ops; } ;
struct TYPE_5__ {int (* iter ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int
hx509_certs_next_cert(hx509_context context,
		      hx509_certs certs,
		      hx509_cursor cursor,
		      hx509_cert *cert)
{
    *cert = NULL;
    return (*certs->ops->iter)(context, certs, certs->ops_data, cursor, cert);
}