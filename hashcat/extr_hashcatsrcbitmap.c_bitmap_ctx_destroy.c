#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* bitmap_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_6__ {int enabled; int /*<<< orphan*/  bitmap_s2_d; int /*<<< orphan*/  bitmap_s2_c; int /*<<< orphan*/  bitmap_s2_b; int /*<<< orphan*/  bitmap_s2_a; int /*<<< orphan*/  bitmap_s1_d; int /*<<< orphan*/  bitmap_s1_c; int /*<<< orphan*/  bitmap_s1_b; int /*<<< orphan*/  bitmap_s1_a; } ;
typedef  TYPE_2__ bitmap_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void bitmap_ctx_destroy (hashcat_ctx_t *hashcat_ctx)
{
  bitmap_ctx_t *bitmap_ctx = hashcat_ctx->bitmap_ctx;

  if (bitmap_ctx->enabled == false) return;

  hcfree (bitmap_ctx->bitmap_s1_a);
  hcfree (bitmap_ctx->bitmap_s1_b);
  hcfree (bitmap_ctx->bitmap_s1_c);
  hcfree (bitmap_ctx->bitmap_s1_d);
  hcfree (bitmap_ctx->bitmap_s2_a);
  hcfree (bitmap_ctx->bitmap_s2_b);
  hcfree (bitmap_ctx->bitmap_s2_c);
  hcfree (bitmap_ctx->bitmap_s2_d);

  memset (bitmap_ctx, 0, sizeof (bitmap_ctx_t));
}