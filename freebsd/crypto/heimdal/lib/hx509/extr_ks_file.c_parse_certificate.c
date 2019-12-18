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
struct hx509_collector {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_pem_header ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int _hx509_collector_certs_add (int /*<<< orphan*/ ,struct hx509_collector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ ) ; 
 int hx509_cert_init_data (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parse_certificate(hx509_context context, const char *fn,
		  struct hx509_collector *c,
		  const hx509_pem_header *headers,
		  const void *data, size_t len,
		  const AlgorithmIdentifier *ai)
{
    hx509_cert cert;
    int ret;

    ret = hx509_cert_init_data(context, data, len, &cert);
    if (ret)
	return ret;

    ret = _hx509_collector_certs_add(context, c, cert);
    hx509_cert_free(cert);
    return ret;
}