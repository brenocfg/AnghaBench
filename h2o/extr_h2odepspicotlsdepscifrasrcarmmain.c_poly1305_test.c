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
typedef  int /*<<< orphan*/  cf_poly1305 ;
typedef  int /*<<< orphan*/  cf_aes_context ;

/* Variables and functions */
 int /*<<< orphan*/  cf_aes_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_aes_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_poly1305_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_poly1305_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_poly1305_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_message ; 
 int /*<<< orphan*/  mac_message_len ; 

__attribute__((used)) static void poly1305_test(void)
{
  uint8_t key[32] = { 0 },
          nonce[16] = { 0 },
          encnonce[16],
          mac[16];

  cf_aes_context aes;
  cf_aes_init(&aes, key, 16);
  cf_aes_encrypt(&aes, nonce, encnonce);

  cf_poly1305 poly;
  cf_poly1305_init(&poly, key + 16, encnonce);
  cf_poly1305_update(&poly, mac_message, mac_message_len);
  cf_poly1305_finish(&poly, mac);
}