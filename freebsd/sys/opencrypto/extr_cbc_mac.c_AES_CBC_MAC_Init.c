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
struct aes_cbc_mac_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct aes_cbc_mac_ctx*,int) ; 

void
AES_CBC_MAC_Init(struct aes_cbc_mac_ctx *ctx)
{
	bzero(ctx, sizeof(*ctx));
}