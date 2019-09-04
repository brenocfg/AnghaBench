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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {size_t last_byte_bits_; scalar_t__ last_byte_; } ;
typedef  TYPE_1__ BrotliEncoderState ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliWriteBits (int,size_t const,size_t*,scalar_t__*) ; 
 int Log2FloorNonZero (int) ; 

__attribute__((used)) static size_t WriteMetadataHeader(
    BrotliEncoderState* s, const size_t block_size, uint8_t* header) {
  size_t storage_ix;
  storage_ix = s->last_byte_bits_;
  header[0] = s->last_byte_;
  s->last_byte_ = 0;
  s->last_byte_bits_ = 0;

  BrotliWriteBits(1, 0, &storage_ix, header);
  BrotliWriteBits(2, 3, &storage_ix, header);
  BrotliWriteBits(1, 0, &storage_ix, header);
  if (block_size == 0) {
    BrotliWriteBits(2, 0, &storage_ix, header);
  } else {
    uint32_t nbits = (block_size == 1) ? 0 :
        (Log2FloorNonZero((uint32_t)block_size - 1) + 1);
    uint32_t nbytes = (nbits + 7) / 8;
    BrotliWriteBits(2, nbytes, &storage_ix, header);
    BrotliWriteBits(8 * nbytes, block_size - 1, &storage_ix, header);
  }
  return (storage_ix + 7u) >> 3;
}