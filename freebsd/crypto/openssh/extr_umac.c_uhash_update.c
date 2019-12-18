#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uhash_ctx_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  long UWORD ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {long msg_len; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 long L1_KEY_LEN ; 
 int STREAMS ; 
 int /*<<< orphan*/  nh (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,long,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nh_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nh_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,long) ; 
 int /*<<< orphan*/  poly_hash (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uhash_update(uhash_ctx_t ctx, const u_char *input, long len)
/* Given len bytes of data, we parse it into L1_KEY_LEN chunks and
 * hash each one with NH, calling the polyhash on each NH output.
 */
{
    UWORD bytes_hashed, bytes_remaining;
    UINT64 result_buf[STREAMS];
    UINT8 *nh_result = (UINT8 *)&result_buf;

    if (ctx->msg_len + len <= L1_KEY_LEN) {
        nh_update(&ctx->hash, (const UINT8 *)input, len);
        ctx->msg_len += len;
    } else {

         bytes_hashed = ctx->msg_len % L1_KEY_LEN;
         if (ctx->msg_len == L1_KEY_LEN)
             bytes_hashed = L1_KEY_LEN;

         if (bytes_hashed + len >= L1_KEY_LEN) {

             /* If some bytes have been passed to the hash function      */
             /* then we want to pass at most (L1_KEY_LEN - bytes_hashed) */
             /* bytes to complete the current nh_block.                  */
             if (bytes_hashed) {
                 bytes_remaining = (L1_KEY_LEN - bytes_hashed);
                 nh_update(&ctx->hash, (const UINT8 *)input, bytes_remaining);
                 nh_final(&ctx->hash, nh_result);
                 ctx->msg_len += bytes_remaining;
                 poly_hash(ctx,(UINT32 *)nh_result);
                 len -= bytes_remaining;
                 input += bytes_remaining;
             }

             /* Hash directly from input stream if enough bytes */
             while (len >= L1_KEY_LEN) {
                 nh(&ctx->hash, (const UINT8 *)input, L1_KEY_LEN,
                                   L1_KEY_LEN, nh_result);
                 ctx->msg_len += L1_KEY_LEN;
                 len -= L1_KEY_LEN;
                 input += L1_KEY_LEN;
                 poly_hash(ctx,(UINT32 *)nh_result);
             }
         }

         /* pass remaining < L1_KEY_LEN bytes of input data to NH */
         if (len) {
             nh_update(&ctx->hash, (const UINT8 *)input, len);
             ctx->msg_len += len;
         }
     }

    return (1);
}