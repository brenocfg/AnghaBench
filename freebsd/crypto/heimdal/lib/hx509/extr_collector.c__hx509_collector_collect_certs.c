#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t len; int /*<<< orphan*/ * data; } ;
struct hx509_collector {TYPE_1__ val; int /*<<< orphan*/  certs; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/ * hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ **) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int hx509_certs_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int match_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int match_localkeyid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
_hx509_collector_collect_certs(hx509_context context,
			       struct hx509_collector *c,
			       hx509_certs *ret_certs)
{
    hx509_certs certs;
    int ret;
    size_t i;

    *ret_certs = NULL;

    ret = hx509_certs_init(context, "MEMORY:collector-store", 0, NULL, &certs);
    if (ret)
	return ret;

    ret = hx509_certs_merge(context, certs, c->certs);
    if (ret) {
	hx509_certs_free(&certs);
	return ret;
    }

    for (i = 0; i < c->val.len; i++) {
	ret = match_localkeyid(context, c->val.data[i], certs);
	if (ret == 0)
	    continue;
	ret = match_keys(context, c->val.data[i], certs);
	if (ret == 0)
	    continue;
    }

    *ret_certs = certs;

    return 0;
}