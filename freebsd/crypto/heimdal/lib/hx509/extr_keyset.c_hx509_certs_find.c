#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_query ;
typedef  int /*<<< orphan*/  hx509_cursor ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_2__* hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;
struct TYPE_9__ {int /*<<< orphan*/  ops_data; TYPE_1__* ops; } ;
struct TYPE_8__ {int (* query ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int HX509_CERT_NOT_FOUND ; 
 scalar_t__ _hx509_query_match_cert (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hx509_query_statistic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_end_seq (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int hx509_certs_next_cert (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int hx509_certs_start_seq (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 

int
hx509_certs_find(hx509_context context,
		 hx509_certs certs,
		 const hx509_query *q,
		 hx509_cert *r)
{
    hx509_cursor cursor;
    hx509_cert c;
    int ret;

    *r = NULL;

    _hx509_query_statistic(context, 0, q);

    if (certs->ops->query)
	return (*certs->ops->query)(context, certs, certs->ops_data, q, r);

    ret = hx509_certs_start_seq(context, certs, &cursor);
    if (ret)
	return ret;

    c = NULL;
    while (1) {
	ret = hx509_certs_next_cert(context, certs, cursor, &c);
	if (ret)
	    break;
	if (c == NULL)
	    break;
	if (_hx509_query_match_cert(context, q, c)) {
	    *r = c;
	    break;
	}
	hx509_cert_free(c);
    }

    hx509_certs_end_seq(context, certs, cursor);
    if (ret)
	return ret;
    /**
     * Return HX509_CERT_NOT_FOUND if no certificate in certs matched
     * the query.
     */
    if (c == NULL) {
	hx509_clear_error_string(context);
	return HX509_CERT_NOT_FOUND;
    }

    return 0;
}