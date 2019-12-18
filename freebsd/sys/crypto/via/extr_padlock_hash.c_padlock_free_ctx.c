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
struct auth_hash {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CRYPTO_SHA1_HMAC ; 
 scalar_t__ CRYPTO_SHA2_256_HMAC ; 
 int VIA_HAS_SHA ; 
 int /*<<< orphan*/  padlock_sha_free (void*) ; 
 int via_feature_xcrypt ; 

__attribute__((used)) static void
padlock_free_ctx(struct auth_hash *axf, void *ctx)
{

	if ((via_feature_xcrypt & VIA_HAS_SHA) != 0 &&
	    (axf->type == CRYPTO_SHA1_HMAC ||
	     axf->type == CRYPTO_SHA2_256_HMAC)) {
		padlock_sha_free(ctx);
	}
}