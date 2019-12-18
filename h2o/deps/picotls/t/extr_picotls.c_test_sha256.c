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
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CIPHER_SUITE_AES_128_GCM_SHA256 ; 
 int /*<<< orphan*/  ctx ; 
 TYPE_1__* find_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_sha256(void)
{
    test_hash(find_cipher(ctx, PTLS_CIPHER_SUITE_AES_128_GCM_SHA256)->hash);
}