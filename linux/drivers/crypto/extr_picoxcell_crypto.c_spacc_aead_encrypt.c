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
struct spacc_aead {int /*<<< orphan*/  type; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_aead_alg (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int spacc_aead_setup (struct aead_request*,int /*<<< orphan*/ ,int) ; 
 struct spacc_aead* to_spacc_aead (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spacc_aead_encrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct spacc_aead *alg = to_spacc_aead(crypto_aead_alg(aead));

	return spacc_aead_setup(req, alg->type, 1);
}