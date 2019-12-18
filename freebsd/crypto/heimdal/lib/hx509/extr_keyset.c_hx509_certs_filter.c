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
typedef  int /*<<< orphan*/  hx509_query ;
typedef  int /*<<< orphan*/  hx509_cursor ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;

/* Variables and functions */
 int HX509_CERT_NOT_FOUND ; 
 scalar_t__ _hx509_query_match_cert (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hx509_query_statistic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_end_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_certs_next_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int hx509_certs_start_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 

int
hx509_certs_filter(hx509_context context,
		   hx509_certs certs,
		   const hx509_query *q,
		   hx509_certs *result)
{
    hx509_cursor cursor;
    hx509_cert c;
    int ret, found = 0;

    _hx509_query_statistic(context, 0, q);

    ret = hx509_certs_init(context, "MEMORY:filter-certs", 0,
			   NULL, result);
    if (ret)
	return ret;

    ret = hx509_certs_start_seq(context, certs, &cursor);
    if (ret) {
	hx509_certs_free(result);
	return ret;
    }

    c = NULL;
    while (1) {
	ret = hx509_certs_next_cert(context, certs, cursor, &c);
	if (ret)
	    break;
	if (c == NULL)
	    break;
	if (_hx509_query_match_cert(context, q, c)) {
	    hx509_certs_add(context, *result, c);
	    found = 1;
	}
	hx509_cert_free(c);
    }

    hx509_certs_end_seq(context, certs, cursor);
    if (ret) {
	hx509_certs_free(result);
	return ret;
    }

    /**
     * Return HX509_CERT_NOT_FOUND if no certificate in certs matched
     * the query.
     */
    if (!found) {
	hx509_certs_free(result);
	hx509_clear_error_string(context);
	return HX509_CERT_NOT_FOUND;
    }

    return 0;
}