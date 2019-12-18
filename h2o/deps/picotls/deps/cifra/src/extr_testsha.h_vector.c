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
typedef  int /*<<< orphan*/  cf_chash_ctx ;
struct TYPE_3__ {size_t hashsz; size_t blocksz; int /*<<< orphan*/  (* digest ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ cf_chash ;

/* Variables and functions */
 int CF_MAXHASH ; 
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vector(const cf_chash *hash,
                   const void *vmsg, size_t nmsg,
                   const char *expect, size_t nexpect)
{
  uint8_t digest[CF_MAXHASH];
  const uint8_t *msg = vmsg;
  size_t orig_nmsg = nmsg;

  cf_chash_ctx ctx;
  hash->init(&ctx);

  /* Input in carefully chosen chunk sizes to exercise blockwise code. */
  if (nmsg)
  {
    hash->update(&ctx, msg, 1);
    nmsg--;
    msg++;
  }

  hash->update(&ctx, msg, nmsg);
  hash->digest(&ctx, digest);
  TEST_CHECK(nexpect == hash->hashsz);
  TEST_CHECK(memcmp(digest, expect, nexpect) == 0);

  /* Now try with other arrangements. */
  msg = vmsg;
  nmsg = orig_nmsg;

  hash->init(&ctx);
  if (nmsg >= hash->blocksz)
  {
    hash->update(&ctx, msg, hash->blocksz - 1);
    nmsg -= hash->blocksz - 1;
    msg += hash->blocksz - 1;
  }

  hash->update(&ctx, msg, nmsg);
  hash->digest(&ctx, digest);
  TEST_CHECK(memcmp(digest, expect, nexpect) == 0);
}