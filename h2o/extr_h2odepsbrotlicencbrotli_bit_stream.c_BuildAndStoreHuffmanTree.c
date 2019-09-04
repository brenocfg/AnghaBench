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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  depth ;
typedef  int /*<<< orphan*/  HuffmanTree ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliConvertBitDepthsToSymbols (scalar_t__*,size_t const,scalar_t__*) ; 
 int /*<<< orphan*/  BrotliCreateHuffmanTree (scalar_t__ const*,size_t const,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  BrotliStoreHuffmanTree (scalar_t__*,size_t const,int /*<<< orphan*/ *,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  BrotliWriteBits (size_t,size_t,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  StoreSimpleHuffmanTree (scalar_t__*,size_t*,size_t,size_t,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static void BuildAndStoreHuffmanTree(const uint32_t *histogram,
                                     const size_t length,
                                     HuffmanTree* tree,
                                     uint8_t* depth,
                                     uint16_t* bits,
                                     size_t* storage_ix,
                                     uint8_t* storage) {
  size_t count = 0;
  size_t s4[4] = { 0 };
  size_t i;
  size_t max_bits = 0;
  for (i = 0; i < length; i++) {
    if (histogram[i]) {
      if (count < 4) {
        s4[count] = i;
      } else if (count > 4) {
        break;
      }
      count++;
    }
  }

  {
    size_t max_bits_counter = length - 1;
    while (max_bits_counter) {
      max_bits_counter >>= 1;
      ++max_bits;
    }
  }

  if (count <= 1) {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, s4[0], storage_ix, storage);
    depth[s4[0]] = 0;
    bits[s4[0]] = 0;
    return;
  }

  memset(depth, 0, length * sizeof(depth[0]));
  BrotliCreateHuffmanTree(histogram, length, 15, tree, depth);
  BrotliConvertBitDepthsToSymbols(depth, length, bits);

  if (count <= 4) {
    StoreSimpleHuffmanTree(depth, s4, count, max_bits, storage_ix, storage);
  } else {
    BrotliStoreHuffmanTree(depth, length, tree, storage_ix, storage);
  }
}