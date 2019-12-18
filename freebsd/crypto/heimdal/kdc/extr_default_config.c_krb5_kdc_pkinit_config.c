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
struct TYPE_4__ {int enable_pkinit; int /*<<< orphan*/  pkinit_kdc_revoke; int /*<<< orphan*/  pkinit_kdc_cert_pool; int /*<<< orphan*/ * pkinit_kdc_anchors; int /*<<< orphan*/ * pkinit_kdc_identity; int /*<<< orphan*/ * pkinit_kdc_friendly_name; } ;
typedef  TYPE_1__ krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_kdc_pk_initialize (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strdup (char*) ; 

krb5_error_code
krb5_kdc_pkinit_config(krb5_context context, krb5_kdc_configuration *config)
{
#ifdef PKINIT
#ifdef __APPLE__
    config->enable_pkinit = 1;

    if (config->pkinit_kdc_identity == NULL) {
	if (config->pkinit_kdc_friendly_name == NULL)
	    config->pkinit_kdc_friendly_name =
		strdup("O=System Identity,CN=com.apple.kerberos.kdc");
	config->pkinit_kdc_identity = strdup("KEYCHAIN:");
    }
    if (config->pkinit_kdc_anchors == NULL)
	config->pkinit_kdc_anchors = strdup("KEYCHAIN:");

#endif /* __APPLE__ */

    if (config->enable_pkinit) {
	if (config->pkinit_kdc_identity == NULL)
	    krb5_errx(context, 1, "pkinit enabled but no identity");

	if (config->pkinit_kdc_anchors == NULL)
	    krb5_errx(context, 1, "pkinit enabled but no X509 anchors");

	krb5_kdc_pk_initialize(context, config,
			       config->pkinit_kdc_identity,
			       config->pkinit_kdc_anchors,
			       config->pkinit_kdc_cert_pool,
			       config->pkinit_kdc_revoke);

    }

    return 0;
#endif /* PKINIT */
}