#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmpbuf ;
struct TYPE_6__ {unsigned char* opad; } ;
typedef  TYPE_1__ md5_context ;

/* Variables and functions */
 int /*<<< orphan*/  md5_finish (TYPE_1__*,unsigned char*) ; 
 int /*<<< orphan*/  md5_starts (TYPE_1__*) ; 
 int /*<<< orphan*/  md5_update (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void md5_hmac_finish( md5_context *ctx, unsigned char output[16] )
{
    unsigned char tmpbuf[16];

    md5_finish( ctx, tmpbuf );
    md5_starts( ctx );
    md5_update( ctx, ctx->opad, 64 );
    md5_update( ctx, tmpbuf, 16 );
    md5_finish( ctx, output );

    memset( tmpbuf, 0, sizeof( tmpbuf ) );
}