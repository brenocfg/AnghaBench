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
 int /*<<< orphan*/  md5_update (int /*<<< orphan*/ *,unsigned char*,int) ; 

void md5_hmac_update( md5_context *ctx, unsigned char *input, int ilen )
{
    md5_update( ctx, input, ilen );
}