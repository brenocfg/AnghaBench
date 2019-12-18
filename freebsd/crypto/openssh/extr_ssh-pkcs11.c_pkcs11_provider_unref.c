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
struct pkcs11_provider {scalar_t__ refcount; struct pkcs11_provider* slotinfo; struct pkcs11_provider* slotlist; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,struct pkcs11_provider*,scalar_t__) ; 
 int /*<<< orphan*/  error (char*,struct pkcs11_provider*) ; 
 int /*<<< orphan*/  free (struct pkcs11_provider*) ; 

__attribute__((used)) static void
pkcs11_provider_unref(struct pkcs11_provider *p)
{
	debug("pkcs11_provider_unref: %p refcount %d", p, p->refcount);
	if (--p->refcount <= 0) {
		if (p->valid)
			error("pkcs11_provider_unref: %p still valid", p);
		free(p->slotlist);
		free(p->slotinfo);
		free(p);
	}
}