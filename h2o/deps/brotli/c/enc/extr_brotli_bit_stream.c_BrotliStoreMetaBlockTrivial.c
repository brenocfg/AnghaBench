#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_12__ {int /*<<< orphan*/  data_; } ;
struct TYPE_11__ {int /*<<< orphan*/  data_; } ;
struct TYPE_10__ {int /*<<< orphan*/  data_; } ;
typedef  int /*<<< orphan*/  MemoryManager ;
typedef  TYPE_1__ HistogramLiteral ;
typedef  TYPE_2__ HistogramDistance ;
typedef  TYPE_3__ HistogramCommand ;
typedef  int /*<<< orphan*/  Command ;
typedef  scalar_t__ BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_ALLOC (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BROTLI_FREE (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BROTLI_IS_OOM (int /*<<< orphan*/ *) ; 
 int BROTLI_NUM_COMMAND_SYMBOLS ; 
 int BROTLI_NUM_LITERAL_SYMBOLS ; 
 int /*<<< orphan*/  BrotliWriteBits (int,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BuildAndStoreHuffmanTree (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BuildHistograms (int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/  const*,size_t,TYPE_1__*,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  HistogramClearCommand (TYPE_3__*) ; 
 int /*<<< orphan*/  HistogramClearDistance (TYPE_2__*) ; 
 int /*<<< orphan*/  HistogramClearLiteral (TYPE_1__*) ; 
 int HuffmanTree ; 
 int /*<<< orphan*/  JumpToByteBoundary (size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUFFMAN_TREE_SIZE ; 
 int SIMPLE_DISTANCE_ALPHABET_SIZE ; 
 int /*<<< orphan*/  StoreCompressedMetaBlockHeader (scalar_t__,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StoreDataWithHuffmanCodes (int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int tree ; 

void BrotliStoreMetaBlockTrivial(MemoryManager* m,
                                 const uint8_t* input,
                                 size_t start_pos,
                                 size_t length,
                                 size_t mask,
                                 BROTLI_BOOL is_last,
                                 const Command *commands,
                                 size_t n_commands,
                                 size_t *storage_ix,
                                 uint8_t *storage) {
  HistogramLiteral lit_histo;
  HistogramCommand cmd_histo;
  HistogramDistance dist_histo;
  uint8_t lit_depth[BROTLI_NUM_LITERAL_SYMBOLS];
  uint16_t lit_bits[BROTLI_NUM_LITERAL_SYMBOLS];
  uint8_t cmd_depth[BROTLI_NUM_COMMAND_SYMBOLS];
  uint16_t cmd_bits[BROTLI_NUM_COMMAND_SYMBOLS];
  uint8_t dist_depth[SIMPLE_DISTANCE_ALPHABET_SIZE];
  uint16_t dist_bits[SIMPLE_DISTANCE_ALPHABET_SIZE];
  HuffmanTree* tree;

  StoreCompressedMetaBlockHeader(is_last, length, storage_ix, storage);

  HistogramClearLiteral(&lit_histo);
  HistogramClearCommand(&cmd_histo);
  HistogramClearDistance(&dist_histo);

  BuildHistograms(input, start_pos, mask, commands, n_commands,
                  &lit_histo, &cmd_histo, &dist_histo);

  BrotliWriteBits(13, 0, storage_ix, storage);

  tree = BROTLI_ALLOC(m, HuffmanTree, MAX_HUFFMAN_TREE_SIZE);
  if (BROTLI_IS_OOM(m)) return;
  BuildAndStoreHuffmanTree(lit_histo.data_, BROTLI_NUM_LITERAL_SYMBOLS, tree,
                           lit_depth, lit_bits,
                           storage_ix, storage);
  BuildAndStoreHuffmanTree(cmd_histo.data_, BROTLI_NUM_COMMAND_SYMBOLS, tree,
                           cmd_depth, cmd_bits,
                           storage_ix, storage);
  BuildAndStoreHuffmanTree(dist_histo.data_, SIMPLE_DISTANCE_ALPHABET_SIZE,
                           tree,
                           dist_depth, dist_bits,
                           storage_ix, storage);
  BROTLI_FREE(m, tree);
  StoreDataWithHuffmanCodes(input, start_pos, mask, commands,
                            n_commands, lit_depth, lit_bits,
                            cmd_depth, cmd_bits,
                            dist_depth, dist_bits,
                            storage_ix, storage);
  if (is_last) {
    JumpToByteBoundary(storage_ix, storage);
  }
}