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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  istream_t ;
typedef  int /*<<< orphan*/  frame_context_t ;

/* Variables and functions */
 scalar_t__ IO_read_bits (int /*<<< orphan*/ * const,int) ; 
 size_t decode_literals_compressed (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int /*<<< orphan*/ ** const,int,int) ; 
 size_t decode_literals_simple (int /*<<< orphan*/ * const,int /*<<< orphan*/ ** const,int,int) ; 

__attribute__((used)) static size_t decode_literals(frame_context_t *const ctx, istream_t *const in,
                              u8 **const literals) {
    // "Literals can be stored uncompressed or compressed using Huffman prefix
    // codes. When compressed, an optional tree description can be present,
    // followed by 1 or 4 streams."
    //
    // "Literals_Section_Header
    //
    // Header is in charge of describing how literals are packed. It's a
    // byte-aligned variable-size bitfield, ranging from 1 to 5 bytes, using
    // little-endian convention."
    //
    // "Literals_Block_Type
    //
    // This field uses 2 lowest bits of first byte, describing 4 different block
    // types"
    //
    // size_format takes between 1 and 2 bits
    int block_type = (int)IO_read_bits(in, 2);
    int size_format = (int)IO_read_bits(in, 2);

    if (block_type <= 1) {
        // Raw or RLE literals block
        return decode_literals_simple(in, literals, block_type,
                                      size_format);
    } else {
        // Huffman compressed literals
        return decode_literals_compressed(ctx, in, literals, block_type,
                                          size_format);
    }
}