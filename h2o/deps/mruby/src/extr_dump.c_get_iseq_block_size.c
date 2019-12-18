#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {int ilen; } ;
typedef  TYPE_1__ mrb_irep ;

/* Variables and functions */

__attribute__((used)) static size_t
get_iseq_block_size(mrb_state *mrb, mrb_irep *irep)
{
  size_t size = 0;

  size += sizeof(uint32_t); /* ilen */
  size += sizeof(uint32_t); /* max padding */
  size += sizeof(uint32_t) * irep->ilen; /* iseq(n) */

  return size;
}