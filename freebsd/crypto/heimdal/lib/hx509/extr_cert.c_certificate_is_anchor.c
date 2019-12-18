#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  certificate; int /*<<< orphan*/  match; } ;
typedef  TYPE_1__ hx509_query ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/ * hx509_certs ;
typedef  int /*<<< orphan*/  hx509_cert ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_QUERY_MATCH_CERTIFICATE ; 
 int /*<<< orphan*/  _hx509_get_cert (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  _hx509_query_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ ) ; 
 int hx509_certs_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
certificate_is_anchor(hx509_context context,
		      hx509_certs trust_anchors,
		      const hx509_cert cert)
{
    hx509_query q;
    hx509_cert c;
    int ret;

    if (trust_anchors == NULL)
	return 0;

    _hx509_query_clear(&q);

    q.match = HX509_QUERY_MATCH_CERTIFICATE;
    q.certificate = _hx509_get_cert(cert);

    ret = hx509_certs_find(context, trust_anchors, &q, &c);
    if (ret == 0)
	hx509_cert_free(c);
    return ret == 0;
}