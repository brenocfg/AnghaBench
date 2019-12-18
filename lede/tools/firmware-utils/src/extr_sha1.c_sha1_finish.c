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
typedef  int ulong ;
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_4__ {int* total; int* state; } ;
typedef  TYPE_1__ sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  PUT_UINT32_BE (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sha1_padding ; 
 int /*<<< orphan*/  sha1_update (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void sha1_finish( sha1_context *ctx, uchar digest[20] )
{
    ulong last, padn;
    ulong high, low;
    uchar msglen[8];

    high = ( ctx->total[0] >> 29 )
         | ( ctx->total[1] <<  3 );
    low  = ( ctx->total[0] <<  3 );

    PUT_UINT32_BE( high, msglen, 0 );
    PUT_UINT32_BE( low,  msglen, 4 );

    last = ctx->total[0] & 0x3F;
    padn = ( last < 56 ) ? ( 56 - last ) : ( 120 - last );

    sha1_update( ctx, sha1_padding, padn );
    sha1_update( ctx, msglen, 8 );

    PUT_UINT32_BE( ctx->state[0], digest,  0 );
    PUT_UINT32_BE( ctx->state[1], digest,  4 );
    PUT_UINT32_BE( ctx->state[2], digest,  8 );
    PUT_UINT32_BE( ctx->state[3], digest, 12 );
    PUT_UINT32_BE( ctx->state[4], digest, 16 );
}