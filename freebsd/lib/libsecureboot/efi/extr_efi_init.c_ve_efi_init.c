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
typedef  int /*<<< orphan*/  hash_data ;
typedef  int /*<<< orphan*/  br_x509_certificate ;

/* Variables and functions */
 int /*<<< orphan*/ * efi_get_forbidden_certs (size_t*) ; 
 int /*<<< orphan*/ * efi_get_forbidden_digests (size_t*) ; 
 int /*<<< orphan*/ * efi_get_trusted_certs (size_t*) ; 
 int efi_secure_boot_enabled () ; 
 int /*<<< orphan*/  free_certificates (int /*<<< orphan*/ *,size_t) ; 
 size_t ve_forbidden_anchors_add (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ve_forbidden_digest_add (int /*<<< orphan*/ *,size_t) ; 
 size_t ve_trust_anchors_add (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
ve_efi_init(void)
{
	br_x509_certificate *xcs;
	hash_data *digests;
	size_t num;
	int result;
	static int once = 0;

	if (once > 0)
		return;

	once = 1;

	result = efi_secure_boot_enabled();
	if (result <= 0)
		return;

	xcs = efi_get_trusted_certs(&num);
	if (num > 0 && xcs != NULL) {
		num = ve_trust_anchors_add(xcs, num);
		free_certificates(xcs, num);
	}
	xcs = efi_get_forbidden_certs(&num);
	if (num > 0 && xcs != NULL) {
		num = ve_forbidden_anchors_add(xcs, num);
		free_certificates(xcs, num);
	}
	digests = efi_get_forbidden_digests(&num);
	if (num > 0 && digests != NULL) {
		ve_forbidden_digest_add(digests, num);
		/*
		 * Don't free the buffors for digests,
		 * since they are shallow copied.
		 */
		xfree(digests);
	}

	return;
}