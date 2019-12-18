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
struct tlsv1_credentials {struct tlsv1_credentials* ocsp_stapling_response_multi; struct tlsv1_credentials* ocsp_stapling_response; struct tlsv1_credentials* dh_g; struct tlsv1_credentials* dh_p; int /*<<< orphan*/  key; int /*<<< orphan*/  cert; int /*<<< orphan*/  trusted_certs; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_private_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct tlsv1_credentials*) ; 
 int /*<<< orphan*/  x509_certificate_chain_free (int /*<<< orphan*/ ) ; 

void tlsv1_cred_free(struct tlsv1_credentials *cred)
{
	if (cred == NULL)
		return;

	x509_certificate_chain_free(cred->trusted_certs);
	x509_certificate_chain_free(cred->cert);
	crypto_private_key_free(cred->key);
	os_free(cred->dh_p);
	os_free(cred->dh_g);
	os_free(cred->ocsp_stapling_response);
	os_free(cred->ocsp_stapling_response_multi);
	os_free(cred);
}