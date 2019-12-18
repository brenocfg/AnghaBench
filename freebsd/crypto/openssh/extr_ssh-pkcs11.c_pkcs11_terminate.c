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
 struct pkcs11_provider* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pkcs11_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  pkcs11_provider_finalize (struct pkcs11_provider*) ; 
 int /*<<< orphan*/  pkcs11_provider_unref (struct pkcs11_provider*) ; 
 int /*<<< orphan*/  pkcs11_providers ; 

void
pkcs11_terminate(void)
{
	struct pkcs11_provider *p;

	while ((p = TAILQ_FIRST(&pkcs11_providers)) != NULL) {
		TAILQ_REMOVE(&pkcs11_providers, p, next);
		pkcs11_provider_finalize(p);
		pkcs11_provider_unref(p);
	}
}