#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {int entryPageOffset; scalar_t__ entryCount; int encodingsPageOffset; } ;
struct TYPE_5__ {int commonEncodingsArrayCount; int commonEncodingsArraySectionOffset; } ;
struct TYPE_4__ {int secondLevelPagesSectionOffset; } ;
struct baton {TYPE_3__ compressed_second_level_page_header; TYPE_2__ unwind_header; int /*<<< orphan*/ * compact_unwind_start; TYPE_1__ first_level_index_entry; } ;

/* Variables and functions */
 int UNWIND_INFO_COMPRESSED_ENTRY_ENCODING_INDEX (int) ; 
 int UNWIND_INFO_COMPRESSED_ENTRY_FUNC_OFFSET (int) ; 
 int /*<<< orphan*/  print_function_encoding (struct baton,scalar_t__,int,int,int) ; 

void print_second_level_index_compressed(struct baton baton) {
  uint8_t *this_index =
      baton.compact_unwind_start +
      baton.first_level_index_entry.secondLevelPagesSectionOffset;
  uint8_t *start_of_entries =
      this_index + baton.compressed_second_level_page_header.entryPageOffset;
  uint8_t *offset = start_of_entries;
  for (uint16_t idx = 0;
       idx < baton.compressed_second_level_page_header.entryCount; idx++) {
    uint32_t entry = *((uint32_t *)offset);
    offset += 4;
    uint32_t encoding;

    uint32_t entry_encoding_index =
        UNWIND_INFO_COMPRESSED_ENTRY_ENCODING_INDEX(entry);
    uint32_t entry_func_offset =
        UNWIND_INFO_COMPRESSED_ENTRY_FUNC_OFFSET(entry);

    if (entry_encoding_index < baton.unwind_header.commonEncodingsArrayCount) {
      // encoding is in common table in section header
      encoding =
          *((uint32_t *)(baton.compact_unwind_start +
                         baton.unwind_header.commonEncodingsArraySectionOffset +
                         (entry_encoding_index * sizeof(uint32_t))));
    } else {
      // encoding is in page specific table
      uint32_t page_encoding_index =
          entry_encoding_index - baton.unwind_header.commonEncodingsArrayCount;
      encoding = *((uint32_t *)(this_index +
                                baton.compressed_second_level_page_header
                                    .encodingsPageOffset +
                                (page_encoding_index * sizeof(uint32_t))));
    }

    print_function_encoding(baton, idx, encoding, entry_encoding_index,
                            entry_func_offset);
  }
}