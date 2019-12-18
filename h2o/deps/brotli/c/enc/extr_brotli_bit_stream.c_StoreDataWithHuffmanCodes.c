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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_5__ {size_t cmd_prefix_; size_t insert_len_; size_t dist_prefix_; int dist_extra_; } ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliWriteBits (size_t const,size_t const,size_t*,size_t*) ; 
 scalar_t__ CommandCopyLen (TYPE_1__ const*) ; 
 int /*<<< orphan*/  StoreCommandExtra (TYPE_1__ const*,size_t*,size_t*) ; 

__attribute__((used)) static void StoreDataWithHuffmanCodes(const uint8_t* input,
                                      size_t start_pos,
                                      size_t mask,
                                      const Command *commands,
                                      size_t n_commands,
                                      const uint8_t* lit_depth,
                                      const uint16_t* lit_bits,
                                      const uint8_t* cmd_depth,
                                      const uint16_t* cmd_bits,
                                      const uint8_t* dist_depth,
                                      const uint16_t* dist_bits,
                                      size_t* storage_ix,
                                      uint8_t* storage) {
  size_t pos = start_pos;
  size_t i;
  for (i = 0; i < n_commands; ++i) {
    const Command cmd = commands[i];
    const size_t cmd_code = cmd.cmd_prefix_;
    size_t j;
    BrotliWriteBits(
        cmd_depth[cmd_code], cmd_bits[cmd_code], storage_ix, storage);
    StoreCommandExtra(&cmd, storage_ix, storage);
    for (j = cmd.insert_len_; j != 0; --j) {
      const uint8_t literal = input[pos & mask];
      BrotliWriteBits(
          lit_depth[literal], lit_bits[literal], storage_ix, storage);
      ++pos;
    }
    pos += CommandCopyLen(&cmd);
    if (CommandCopyLen(&cmd) && cmd.cmd_prefix_ >= 128) {
      const size_t dist_code = cmd.dist_prefix_;
      const uint32_t distnumextra = cmd.dist_extra_ >> 24;
      const uint32_t distextra = cmd.dist_extra_ & 0xffffff;
      BrotliWriteBits(dist_depth[dist_code], dist_bits[dist_code],
                      storage_ix, storage);
      BrotliWriteBits(distnumextra, distextra, storage_ix, storage);
    }
  }
}