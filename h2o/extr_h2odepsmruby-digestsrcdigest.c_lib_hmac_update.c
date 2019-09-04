#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mrb_hmac {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  picohash_update (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lib_hmac_update(mrb_state *mrb, struct mrb_hmac *hmac, unsigned char *data, mrb_int len)
{
#if MRB_INT_MAX > SIZE_MAX
  if (len > SIZE_MAX) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "too long string (not supported yet)");
  }
#endif
  picohash_update(&hmac->ctx, data, len);
}