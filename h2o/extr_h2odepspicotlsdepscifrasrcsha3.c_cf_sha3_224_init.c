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
typedef  int /*<<< orphan*/  cf_sha3_context ;

/* Variables and functions */
 int /*<<< orphan*/  sha3_init (int /*<<< orphan*/ *,int,int) ; 

void cf_sha3_224_init(cf_sha3_context *ctx)
{
  sha3_init(ctx, 1152, 448);
}