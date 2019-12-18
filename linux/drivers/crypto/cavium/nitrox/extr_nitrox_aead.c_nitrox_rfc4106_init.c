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
struct nitrox_rfc4106_rctx {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int) ; 
 int nitrox_gcm_common_init (struct crypto_aead*) ; 

__attribute__((used)) static int nitrox_rfc4106_init(struct crypto_aead *aead)
{
	int ret;

	ret = nitrox_gcm_common_init(aead);
	if (ret)
		return ret;

	crypto_aead_set_reqsize(aead, sizeof(struct aead_request) +
				sizeof(struct nitrox_rfc4106_rctx));

	return 0;
}