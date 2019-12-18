#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int secondLevelPagesSectionOffset; scalar_t__ functionOffset; } ;
struct TYPE_4__ {int entryPageOffset; scalar_t__ entryCount; } ;
struct baton {TYPE_1__ first_level_index_entry; TYPE_2__ regular_second_level_page_header; int /*<<< orphan*/ * compact_unwind_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_function_encoding (struct baton,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void print_second_level_index_regular(struct baton baton) {
  uint8_t *page_entries =
      baton.compact_unwind_start +
      baton.first_level_index_entry.secondLevelPagesSectionOffset +
      baton.regular_second_level_page_header.entryPageOffset;
  uint32_t entries_count = baton.regular_second_level_page_header.entryCount;

  uint8_t *offset = page_entries;

  uint32_t idx = 0;
  while (idx < entries_count) {
    uint32_t func_offset = *((uint32_t *)(offset));
    uint32_t encoding = *((uint32_t *)(offset + 4));

    // UNWIND_SECOND_LEVEL_REGULAR entries have a funcOffset which includes the
    // functionOffset from the containing index table already.
    // UNWIND_SECOND_LEVEL_COMPRESSED
    // entries only have the offset from the containing index table
    // functionOffset.
    // So strip off the containing index table functionOffset value here so they
    // can
    // be treated the same at the lower layers.

    print_function_encoding(baton, idx, encoding, (uint32_t)-1,
                            func_offset -
                                baton.first_level_index_entry.functionOffset);
    idx++;
    offset += 8;
  }
}