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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  cf_hmac_ctx ;
typedef  int /*<<< orphan*/  cf_chash ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cf_hmac_finish (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cf_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  cf_hmac_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void cf_hmac(const uint8_t *key, size_t nkey,
             const uint8_t *msg, size_t nmsg,
             uint8_t *out,
             const cf_chash *hash)
{
  cf_hmac_ctx ctx;
  
  assert(out);
  assert(hash);

  cf_hmac_init(&ctx, hash, key, nkey);
  cf_hmac_update(&ctx, msg, nmsg);
  cf_hmac_finish(&ctx, out);
}