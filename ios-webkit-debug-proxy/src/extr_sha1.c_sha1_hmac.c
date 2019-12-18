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
typedef  int /*<<< orphan*/  sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sha1_hmac_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  sha1_hmac_starts (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  sha1_hmac_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

void sha1_hmac( const unsigned char *key, size_t keylen,
                const unsigned char *input, size_t ilen,
                unsigned char output[20] )
{
    sha1_context ctx;

    sha1_hmac_starts( &ctx, key, keylen );
    sha1_hmac_update( &ctx, input, ilen );
    sha1_hmac_finish( &ctx, output );

    memset( &ctx, 0, sizeof( sha1_context ) );
}