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
struct TYPE_3__ {int /*<<< orphan*/  gh; int /*<<< orphan*/  ctr; } ;
typedef  TYPE_1__ cf_gcm_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  cf_ctr_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ghash_add_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

void cf_gcm_encrypt_update(cf_gcm_ctx *gcmctx, const uint8_t *plain, size_t nplain, uint8_t *cipher)
{
  cf_ctr_cipher(&gcmctx->ctr, plain, cipher, nplain);
  ghash_add_cipher(&gcmctx->gh, cipher, nplain);
}