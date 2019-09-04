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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  cf_hmac_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  cf_hmac_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_hmac_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_sha256 ; 
 int /*<<< orphan*/  mac_message ; 
 int /*<<< orphan*/  mac_message_len ; 

__attribute__((used)) static void hmacsha256_test(void)
{
  uint8_t key[32] = { 0 },
          mac[32] = { 0 };

  cf_hmac_ctx ctx;
  cf_hmac_init(&ctx, &cf_sha256, key, sizeof key);
  cf_hmac_update(&ctx, mac_message, mac_message_len);
  cf_hmac_finish(&ctx, mac);
}