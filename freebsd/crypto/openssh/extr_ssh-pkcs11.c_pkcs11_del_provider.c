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
struct pkcs11_provider {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pkcs11_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  pkcs11_provider_finalize (struct pkcs11_provider*) ; 
 struct pkcs11_provider* pkcs11_provider_lookup (char*) ; 
 int /*<<< orphan*/  pkcs11_provider_unref (struct pkcs11_provider*) ; 
 int /*<<< orphan*/  pkcs11_providers ; 

int
pkcs11_del_provider(char *provider_id)
{
	struct pkcs11_provider *p;

	if ((p = pkcs11_provider_lookup(provider_id)) != NULL) {
		TAILQ_REMOVE(&pkcs11_providers, p, next);
		pkcs11_provider_finalize(p);
		pkcs11_provider_unref(p);
		return (0);
	}
	return (-1);
}