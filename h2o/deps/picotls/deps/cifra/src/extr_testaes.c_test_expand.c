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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ const* ks; } ;
typedef  TYPE_1__ cf_aes_context ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_aes_init (TYPE_1__*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void test_expand(const uint8_t *key, size_t nkey,
                        const uint32_t *answer, size_t roundkeys)
{
  cf_aes_context ctx;

  cf_aes_init(&ctx, key, nkey);

  for (size_t i = 0; i < roundkeys; i++)
  {
    TEST_CHECK(ctx.ks[i] == answer[i]);
  }
}