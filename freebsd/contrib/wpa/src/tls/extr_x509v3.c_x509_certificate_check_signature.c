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
struct x509_certificate {int /*<<< orphan*/  tbs_cert_len; int /*<<< orphan*/  tbs_cert_start; int /*<<< orphan*/  sign_value_len; int /*<<< orphan*/  sign_value; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int x509_check_signature (struct x509_certificate*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int x509_certificate_check_signature(struct x509_certificate *issuer,
				     struct x509_certificate *cert)
{
	return x509_check_signature(issuer, &cert->signature,
				    cert->sign_value, cert->sign_value_len,
				    cert->tbs_cert_start, cert->tbs_cert_len);
}