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
 int /*<<< orphan*/  sha1_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

void sha1_hmac_update( sha1_context *ctx, const unsigned char *input, size_t ilen )
{
    sha1_update( ctx, input, ilen );
}