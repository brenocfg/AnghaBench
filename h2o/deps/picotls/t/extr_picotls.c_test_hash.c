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
struct TYPE_4__ {int /*<<< orphan*/  digest_size; int /*<<< orphan*/  empty_digest; } ;
typedef  TYPE_1__ ptls_hash_algorithm_t ;

/* Variables and functions */
 int PTLS_MAX_DIGEST_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 
 int ptls_calc_hash (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_hash(ptls_hash_algorithm_t *hash)
{
    uint8_t digest[PTLS_MAX_DIGEST_SIZE];
    int ret = ptls_calc_hash(hash, digest, "", 0);
    ok(ret == 0);
    ok(memcmp(digest, hash->empty_digest, hash->digest_size) == 0);
}