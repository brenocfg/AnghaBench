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
struct skcipher_request {int dummy; } ;
struct nitrox_kcrypt_request {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct nitrox_kcrypt_request* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static void free_src_sglist(struct skcipher_request *skreq)
{
	struct nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);

	kfree(nkreq->src);
}