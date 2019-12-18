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
typedef  int u8 ;
typedef  int /*<<< orphan*/  sequence_command_t ;
typedef  int /*<<< orphan*/  istream_t ;
typedef  int /*<<< orphan*/  frame_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ALLOC () ; 
 int IO_read_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decompress_sequences (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

__attribute__((used)) static size_t decode_sequences(frame_context_t *const ctx, istream_t *in,
                               sequence_command_t **const sequences) {
    // "A compressed block is a succession of sequences . A sequence is a
    // literal copy command, followed by a match copy command. A literal copy
    // command specifies a length. It is the number of bytes to be copied (or
    // extracted) from the literal section. A match copy command specifies an
    // offset and a length. The offset gives the position to copy from, which
    // can be within a previous block."

    size_t num_sequences;

    // "Number_of_Sequences
    //
    // This is a variable size field using between 1 and 3 bytes. Let's call its
    // first byte byte0."
    u8 header = IO_read_bits(in, 8);
    if (header == 0) {
        // "There are no sequences. The sequence section stops there.
        // Regenerated content is defined entirely by literals section."
        *sequences = NULL;
        return 0;
    } else if (header < 128) {
        // "Number_of_Sequences = byte0 . Uses 1 byte."
        num_sequences = header;
    } else if (header < 255) {
        // "Number_of_Sequences = ((byte0-128) << 8) + byte1 . Uses 2 bytes."
        num_sequences = ((header - 128) << 8) + IO_read_bits(in, 8);
    } else {
        // "Number_of_Sequences = byte1 + (byte2<<8) + 0x7F00 . Uses 3 bytes."
        num_sequences = IO_read_bits(in, 16) + 0x7F00;
    }

    *sequences = malloc(num_sequences * sizeof(sequence_command_t));
    if (!*sequences) {
        BAD_ALLOC();
    }

    decompress_sequences(ctx, in, *sequences, num_sequences);
    return num_sequences;
}