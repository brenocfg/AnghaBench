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
typedef  int /*<<< orphan*/  hx509_peer_info ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int hx509_certs_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_cms_create_signed (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,void const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

int
hx509_cms_create_signed_1(hx509_context context,
			  int flags,
			  const heim_oid *eContentType,
			  const void *data, size_t length,
			  const AlgorithmIdentifier *digest_alg,
			  hx509_cert cert,
			  hx509_peer_info peer,
			  hx509_certs anchors,
			  hx509_certs pool,
			  heim_octet_string *signed_data)
{
    hx509_certs certs;
    int ret = 0;

    signed_data->data = NULL;
    signed_data->length = 0;

    ret = hx509_certs_init(context, "MEMORY:certs", 0, NULL, &certs);
    if (ret)
	return ret;
    ret = hx509_certs_add(context, certs, cert);
    if (ret)
	goto out;

    ret = hx509_cms_create_signed(context, flags, eContentType, data, length,
				  digest_alg, certs, peer, anchors, pool,
				  signed_data);

 out:
    hx509_certs_free(&certs);
    return ret;
}