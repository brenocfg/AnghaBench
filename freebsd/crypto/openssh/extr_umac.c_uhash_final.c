#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uhash_ctx_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_7__ {int msg_len; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int L1_KEY_LEN ; 
 int STREAMS ; 
 int /*<<< orphan*/  ip_long (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_short (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nh_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poly_hash (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhash_reset (TYPE_1__*) ; 

__attribute__((used)) static int uhash_final(uhash_ctx_t ctx, u_char *res)
/* Incorporate any pending data, pad, and generate tag */
{
    UINT64 result_buf[STREAMS];
    UINT8 *nh_result = (UINT8 *)&result_buf;

    if (ctx->msg_len > L1_KEY_LEN) {
        if (ctx->msg_len % L1_KEY_LEN) {
            nh_final(&ctx->hash, nh_result);
            poly_hash(ctx,(UINT32 *)nh_result);
        }
        ip_long(ctx, res);
    } else {
        nh_final(&ctx->hash, nh_result);
        ip_short(ctx,nh_result, res);
    }
    uhash_reset(ctx);
    return (1);
}