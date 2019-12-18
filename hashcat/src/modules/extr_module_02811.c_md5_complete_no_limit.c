#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/ * h; } ;
typedef  TYPE_1__ md5_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  md5_final (TYPE_1__*) ; 
 int /*<<< orphan*/  md5_init (TYPE_1__*) ; 
 int /*<<< orphan*/  md5_update (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void md5_complete_no_limit (u32 digest[4], const u32 *plain, const u32 plain_len)
{
  // plain = u32 tmp_md5_buf[64] so this is compatible

  md5_ctx_t md5_ctx;

  md5_init (&md5_ctx);
  md5_update (&md5_ctx, plain, plain_len);
  md5_final (&md5_ctx);

  digest[0] = md5_ctx.h[0];
  digest[1] = md5_ctx.h[1];
  digest[2] = md5_ctx.h[2];
  digest[3] = md5_ctx.h[3];
}