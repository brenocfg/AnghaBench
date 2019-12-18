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
struct skcipher_request {int /*<<< orphan*/  base; } ;
struct crypto_engine {int dummy; } ;

/* Variables and functions */
 void crypto_finalize_request (struct crypto_engine*,int /*<<< orphan*/ *,int) ; 

void crypto_finalize_skcipher_request(struct crypto_engine *engine,
				      struct skcipher_request *req, int err)
{
	return crypto_finalize_request(engine, &req->base, err);
}