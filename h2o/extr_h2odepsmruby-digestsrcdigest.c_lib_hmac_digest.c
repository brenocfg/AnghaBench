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
struct TYPE_3__ {int /*<<< orphan*/  digest_length; } ;
struct mrb_hmac {TYPE_1__ ctx; } ;
typedef  TYPE_1__ picohash_ctx_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int PICOHASH_MAX_DIGEST_LENGTH ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picohash_final (TYPE_1__*,unsigned char*) ; 

__attribute__((used)) static mrb_value
lib_hmac_digest(mrb_state *mrb, const struct mrb_hmac *hmac)
{
  picohash_ctx_t ctx;
  unsigned char mdstr[PICOHASH_MAX_DIGEST_LENGTH];

  ctx = hmac->ctx;
  picohash_final(&ctx, mdstr);
  return mrb_str_new(mrb, (char *)mdstr, ctx.digest_length);
}