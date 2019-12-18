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
struct sshkey_cert {int /*<<< orphan*/ * signature_key; int /*<<< orphan*/ * principals; int /*<<< orphan*/ * key_id; int /*<<< orphan*/ * extensions; int /*<<< orphan*/ * critical; int /*<<< orphan*/ * certblob; } ;

/* Variables and functions */
 struct sshkey_cert* calloc (int,int) ; 
 int /*<<< orphan*/  cert_free (struct sshkey_cert*) ; 
 void* sshbuf_new () ; 

__attribute__((used)) static struct sshkey_cert *
cert_new(void)
{
	struct sshkey_cert *cert;

	if ((cert = calloc(1, sizeof(*cert))) == NULL)
		return NULL;
	if ((cert->certblob = sshbuf_new()) == NULL ||
	    (cert->critical = sshbuf_new()) == NULL ||
	    (cert->extensions = sshbuf_new()) == NULL) {
		cert_free(cert);
		return NULL;
	}
	cert->key_id = NULL;
	cert->principals = NULL;
	cert->signature_key = NULL;
	return cert;
}