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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {int offset; scalar_t__ literal_length; } ;
typedef  TYPE_1__ sequence_command_t ;

/* Variables and functions */

__attribute__((used)) static size_t compute_offset(sequence_command_t seq, u64 *const offset_hist) {
    size_t offset;
    // Offsets are special, we need to handle the repeat offsets
    if (seq.offset <= 3) {
        // "The first 3 values define a repeated offset and we will call
        // them Repeated_Offset1, Repeated_Offset2, and Repeated_Offset3.
        // They are sorted in recency order, with Repeated_Offset1 meaning
        // 'most recent one'".

        // Use 0 indexing for the array
        u32 idx = seq.offset - 1;
        if (seq.literal_length == 0) {
            // "There is an exception though, when current sequence's
            // literals length is 0. In this case, repeated offsets are
            // shifted by one, so Repeated_Offset1 becomes Repeated_Offset2,
            // Repeated_Offset2 becomes Repeated_Offset3, and
            // Repeated_Offset3 becomes Repeated_Offset1 - 1_byte."
            idx++;
        }

        if (idx == 0) {
            offset = offset_hist[0];
        } else {
            // If idx == 3 then literal length was 0 and the offset was 3,
            // as per the exception listed above
            offset = idx < 3 ? offset_hist[idx] : offset_hist[0] - 1;

            // If idx == 1 we don't need to modify offset_hist[2], since
            // we're using the second-most recent code
            if (idx > 1) {
                offset_hist[2] = offset_hist[1];
            }
            offset_hist[1] = offset_hist[0];
            offset_hist[0] = offset;
        }
    } else {
        // When it's not a repeat offset:
        // "if (Offset_Value > 3) offset = Offset_Value - 3;"
        offset = seq.offset - 3;

        // Shift back history
        offset_hist[2] = offset_hist[1];
        offset_hist[1] = offset_hist[0];
        offset_hist[0] = offset;
    }
    return offset;
}