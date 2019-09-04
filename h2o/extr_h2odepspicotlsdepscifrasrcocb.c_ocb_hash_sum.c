#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  prpctx; TYPE_1__* prp; } ;
typedef  TYPE_2__ ocb ;
typedef  int /*<<< orphan*/  cf_gf128 ;
struct TYPE_4__ {int /*<<< orphan*/  (* encrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int BLOCK ; 
 int /*<<< orphan*/  cf_gf128_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_gf128_frombytes_be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_gf128_tobytes_be (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xor_bb (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ocb_hash_sum(ocb *o, const uint8_t *block,
                         cf_gf128 sum, const cf_gf128 offset)
{
  uint8_t offset_bytes[BLOCK];
  cf_gf128_tobytes_be(offset, offset_bytes);

  uint8_t block_tmp[BLOCK];
  xor_bb(block_tmp, block, offset_bytes, sizeof block_tmp);
  o->prp->encrypt(o->prpctx, block_tmp, block_tmp);

  cf_gf128 tmp;
  cf_gf128_frombytes_be(block_tmp, tmp);
  cf_gf128_add(sum, tmp, sum);
}