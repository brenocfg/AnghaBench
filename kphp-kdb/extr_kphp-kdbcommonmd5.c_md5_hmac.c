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
typedef  int /*<<< orphan*/  md5_context ;

/* Variables and functions */
 int /*<<< orphan*/  md5_hmac_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  md5_hmac_starts (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  md5_hmac_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void md5_hmac( unsigned char *key, int keylen, unsigned char *input, int ilen,
               unsigned char output[16] )
{
    md5_context ctx;

    md5_hmac_starts( &ctx, key, keylen );
    md5_hmac_update( &ctx, input, ilen );
    md5_hmac_finish( &ctx, output );

    memset( &ctx, 0, sizeof( md5_context ) );
}