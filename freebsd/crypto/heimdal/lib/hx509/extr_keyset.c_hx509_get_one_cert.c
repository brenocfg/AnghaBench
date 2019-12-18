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
typedef  int /*<<< orphan*/  hx509_cursor ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;

/* Variables and functions */
 int /*<<< orphan*/  hx509_certs_end_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hx509_certs_next_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int hx509_certs_start_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
hx509_get_one_cert(hx509_context context, hx509_certs certs, hx509_cert *c)
{
    hx509_cursor cursor;
    int ret;

    *c = NULL;

    ret = hx509_certs_start_seq(context, certs, &cursor);
    if (ret)
	return ret;

    ret = hx509_certs_next_cert(context, certs, cursor, c);
    if (ret)
	return ret;

    hx509_certs_end_seq(context, certs, cursor);
    return 0;
}