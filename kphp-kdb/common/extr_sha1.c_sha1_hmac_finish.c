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
typedef  TYPE_1__ sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sha1_finish (TYPE_1__*,unsigned char*) ; 
 int /*<<< orphan*/  sha1_starts (TYPE_1__*) ; 
 int /*<<< orphan*/  sha1_update (TYPE_1__*,unsigned char*,int) ; 

void sha1_hmac_finish( sha1_context *ctx, unsigned char output[20] )
{
    unsigned char tmpbuf[20];

    sha1_finish( ctx, tmpbuf );
    sha1_starts( ctx );
    sha1_update( ctx, ctx->opad, 64 );
    sha1_update( ctx, tmpbuf, 20 );
    sha1_finish( ctx, output );

    memset( tmpbuf, 0, sizeof( tmpbuf ) );
}