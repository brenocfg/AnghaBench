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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {int rlen; struct TYPE_5__** reps; } ;
typedef  TYPE_1__ mrb_irep ;

/* Variables and functions */
 size_t get_debug_record_size (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 size_t write_debug_record_1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
write_debug_record(mrb_state *mrb, mrb_irep *irep, uint8_t *bin, mrb_sym const* filenames, uint16_t filenames_len)
{
  size_t size, len;
  int irep_no;

  size = len = write_debug_record_1(mrb, irep, bin, filenames, filenames_len);
  bin += len;
  for (irep_no = 0; irep_no < irep->rlen; irep_no++) {
    len = write_debug_record(mrb, irep->reps[irep_no], bin, filenames, filenames_len);
    bin += len;
    size += len;
  }

  mrb_assert(size == get_debug_record_size(mrb, irep));
  return size;
}