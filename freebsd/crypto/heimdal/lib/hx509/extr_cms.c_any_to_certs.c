#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_7__ {TYPE_2__* certificates; } ;
struct TYPE_6__ {size_t len; TYPE_1__* val; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ SignedData ;

/* Variables and functions */
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ ) ; 
 int hx509_cert_init_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_certs_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
any_to_certs(hx509_context context, const SignedData *sd, hx509_certs certs)
{
    int ret;
    size_t i;

    if (sd->certificates == NULL)
	return 0;

    for (i = 0; i < sd->certificates->len; i++) {
	hx509_cert c;

	ret = hx509_cert_init_data(context,
				   sd->certificates->val[i].data,
				   sd->certificates->val[i].length,
				   &c);
	if (ret)
	    return ret;
	ret = hx509_certs_add(context, certs, c);
	hx509_cert_free(c);
	if (ret)
	    return ret;
    }

    return 0;
}