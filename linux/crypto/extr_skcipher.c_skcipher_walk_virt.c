#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct skcipher_walk {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int flags; } ;
struct skcipher_request {TYPE_1__ base; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  SKCIPHER_WALK_PHYS ; 
 int /*<<< orphan*/  SKCIPHER_WALK_SLEEP ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int skcipher_walk_skcipher (struct skcipher_walk*,struct skcipher_request*) ; 

int skcipher_walk_virt(struct skcipher_walk *walk,
		       struct skcipher_request *req, bool atomic)
{
	int err;

	might_sleep_if(req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);

	walk->flags &= ~SKCIPHER_WALK_PHYS;

	err = skcipher_walk_skcipher(walk, req);

	walk->flags &= atomic ? ~SKCIPHER_WALK_SLEEP : ~0;

	return err;
}