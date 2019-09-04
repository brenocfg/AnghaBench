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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ norx32_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_TAG ; 
 int /*<<< orphan*/  permute (TYPE_1__*) ; 
 int /*<<< orphan*/  switch_domain (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_tag(norx32_ctx *ctx, uint8_t tag[16])
{
  switch_domain(ctx, DOMAIN_TAG);
  permute(ctx);
  write32_le(ctx->s[0], tag + 0);
  write32_le(ctx->s[1], tag + 4);
  write32_le(ctx->s[2], tag + 8);
  write32_le(ctx->s[3], tag + 12);
}