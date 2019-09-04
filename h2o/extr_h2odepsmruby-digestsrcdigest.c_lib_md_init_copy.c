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
struct mrb_md {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  picohash_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lib_md_init_copy(mrb_state *mrb, struct mrb_md *mdnew, struct mrb_md *mdold)
{
  mdnew->ctx = mdold->ctx;
  picohash_reset(&mdnew->ctx);
}