#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dataq; } ;
struct virtio_crypto_sym_request {TYPE_2__ base; int /*<<< orphan*/  iv; } ;
struct ablkcipher_request {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_finalize_ablkcipher_request (int /*<<< orphan*/ ,struct ablkcipher_request*,int) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtcrypto_clear_request (TYPE_2__*) ; 

__attribute__((used)) static void virtio_crypto_ablkcipher_finalize_req(
	struct virtio_crypto_sym_request *vc_sym_req,
	struct ablkcipher_request *req,
	int err)
{
	crypto_finalize_ablkcipher_request(vc_sym_req->base.dataq->engine,
					   req, err);
	kzfree(vc_sym_req->iv);
	virtcrypto_clear_request(&vc_sym_req->base);
}