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
struct TYPE_5__ {int /*<<< orphan*/  ipad; } ;
typedef  TYPE_1__ sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  sha1_starts (TYPE_1__*) ; 
 int /*<<< orphan*/  sha1_update (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void sha1_hmac_reset( sha1_context *ctx )
{
    sha1_starts( ctx );
    sha1_update( ctx, ctx->ipad, 64 );
}