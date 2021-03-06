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
typedef  int /*<<< orphan*/  cf_sha256_context ;

/* Variables and functions */
 int /*<<< orphan*/  cf_sha256_update (int /*<<< orphan*/ *,void const*,size_t) ; 

void cf_sha224_update(cf_sha256_context *ctx, const void *data, size_t nbytes)
{
  cf_sha256_update(ctx, data, nbytes);
}