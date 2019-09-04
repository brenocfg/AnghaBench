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
typedef  int /*<<< orphan*/  cf_cbcmac_stream ;
typedef  int /*<<< orphan*/  cf_aes_context ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_aes ; 
 int /*<<< orphan*/  cf_aes_init (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  cf_cbcmac_stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_cbcmac_stream_pad_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_cbcmac_stream_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static void cbcmac_vector(const void *tag_expect, size_t ntag,
                          const void *key, size_t nkey,
                          const void *msg, size_t nmsg)
{
  uint8_t tag[16];

  cf_aes_context aes;
  cf_aes_init(&aes, key, nkey);

  cf_cbcmac_stream cm;
  cf_cbcmac_stream_init(&cm, &cf_aes, &aes);
  cf_cbcmac_stream_update(&cm, msg, nmsg);
  cf_cbcmac_stream_pad_final(&cm, tag);

  TEST_CHECK(sizeof tag == ntag);
  TEST_CHECK(memcmp(tag, tag_expect, sizeof tag) == 0);
}