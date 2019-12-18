#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_7__ {size_t literal_length; size_t match_length; } ;
typedef  TYPE_1__ sequence_command_t ;
typedef  int /*<<< orphan*/  ostream_t ;
typedef  int /*<<< orphan*/  istream_t ;
struct TYPE_8__ {size_t current_total_output; int /*<<< orphan*/ * previous_offsets; } ;
typedef  TYPE_2__ frame_context_t ;

/* Variables and functions */
 size_t IO_istream_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IO_make_istream (int /*<<< orphan*/  const* const,size_t const) ; 
 size_t compute_offset (TYPE_1__ const,int /*<<< orphan*/ * const) ; 
 scalar_t__ copy_literals (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  execute_match_copy (TYPE_2__* const,size_t const,size_t const,size_t,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static void execute_sequences(frame_context_t *const ctx, ostream_t *const out,
                              const u8 *const literals,
                              const size_t literals_len,
                              const sequence_command_t *const sequences,
                              const size_t num_sequences) {
    istream_t litstream = IO_make_istream(literals, literals_len);

    u64 *const offset_hist = ctx->previous_offsets;
    size_t total_output = ctx->current_total_output;

    for (size_t i = 0; i < num_sequences; i++) {
        const sequence_command_t seq = sequences[i];
        {
            const u32 literals_size = copy_literals(seq.literal_length, &litstream, out);
            total_output += literals_size;
        }

        size_t const offset = compute_offset(seq, offset_hist);

        size_t const match_length = seq.match_length;

        execute_match_copy(ctx, offset, match_length, total_output, out);

        total_output += match_length;
    }

    // Copy any leftover literals
    {
        size_t len = IO_istream_len(&litstream);
        copy_literals(len, &litstream, out);
        total_output += len;
    }

    ctx->current_total_output = total_output;
}