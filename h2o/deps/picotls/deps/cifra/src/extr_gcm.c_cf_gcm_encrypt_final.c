#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  e_Y0; int /*<<< orphan*/  gh; } ;
typedef  TYPE_1__ uint8_t ;
typedef  TYPE_1__ cf_gcm_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ghash_final (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mem_clean (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xor_bb (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

void cf_gcm_encrypt_final(cf_gcm_ctx *gcmctx, uint8_t *tag, size_t ntag)
{
  /* Post-process ghash output */
  uint8_t full_tag[16] = { 0 };
  ghash_final(&gcmctx->gh, full_tag);
  
  assert(ntag > 1 && ntag <= 16);
  xor_bb(tag, full_tag, gcmctx->e_Y0, ntag);

  mem_clean(full_tag, sizeof full_tag);
  mem_clean(gcmctx, sizeof *gcmctx);
}