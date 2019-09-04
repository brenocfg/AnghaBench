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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  cf_chash_ctx ;
struct TYPE_3__ {size_t hashsz; int /*<<< orphan*/  (* digest ) (int /*<<< orphan*/ *,int*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,int*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ cf_chash ;

/* Variables and functions */
 int CF_MAXHASH ; 
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 scalar_t__ memcmp (void const*,int*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int*,size_t) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static inline void vector_length(const cf_chash *h,
                                 size_t max,
                                 const void *expect, size_t nexpect)
{
  cf_chash_ctx outer, inner;
  uint8_t digest[CF_MAXHASH];

  h->init(&outer);

  for (size_t n = 0; n < max; n++)
  {
    h->init(&inner);
    
    for (size_t i = 0; i < n; i++)
    {
      uint8_t byte = (uint8_t) n & 0xff;
      h->update(&inner, &byte, 1);
    }

    h->digest(&inner, digest);

    h->update(&outer, digest, h->hashsz);
  }

  h->digest(&outer, digest);

  TEST_CHECK(h->hashsz == nexpect);
  TEST_CHECK(memcmp(expect, digest, nexpect) == 0);
}