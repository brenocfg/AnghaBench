#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  hashsz; } ;
typedef  TYPE_1__ cf_chash ;

/* Variables and functions */
 int CF_MAXHASH ; 
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_hmac (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void hmac_test_sha1(const cf_chash *hash,
                                  const char *long_key,
                                  const char *long_message)
{
  uint8_t sig[CF_MAXHASH];
  uint8_t key[80], message[73];

  /* Key: 0xaa * 80
   * Message: "Test Using Larger Than Block-Size Key - Hash Key First"
   */
  memset(key, 0xaa, 80);
  memcpy(message, "Test Using Larger Than Block-Size Key - Hash Key First", 54);
  cf_hmac(key, 80, message, 54, sig, hash);
  TEST_CHECK(memcmp(sig, long_key, hash->hashsz) == 0);

  /* Key: 0xaa * 80
   * Message: "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data"
   */
  memset(key, 0xaa, 80);
  memcpy(message, "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data", 73);
  cf_hmac(key, 80, message, 73, sig, hash);
  TEST_CHECK(memcmp(sig, long_message, hash->hashsz) == 0);
}