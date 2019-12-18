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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_BYTEORDER_NONATIVE ; 
 int /*<<< orphan*/  dump_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dump_irep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 

int
mrb_dump_irep(mrb_state *mrb, mrb_irep *irep, uint8_t flags, uint8_t **bin, size_t *bin_size)
{
  return dump_irep(mrb, irep, dump_flags(flags, FLAG_BYTEORDER_NONATIVE), bin, bin_size);
}