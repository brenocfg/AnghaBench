#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ ptls_cipher_suite_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CIPHER_SUITE_AES_256_GCM_SHA384 ; 
 int /*<<< orphan*/  ctx ; 
 TYPE_1__* find_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_sha384(void)
{
    ptls_cipher_suite_t *cs = find_cipher(ctx, PTLS_CIPHER_SUITE_AES_256_GCM_SHA384);
    if (cs != NULL)
        test_hash(cs->hash);
}