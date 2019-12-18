#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__* u8; } ;
struct TYPE_5__ {int last_byte_; size_t last_byte_bits_; int available_out_; scalar_t__* next_out_; TYPE_1__ tiny_buf_; } ;
typedef  TYPE_2__ BrotliEncoderState ;

/* Variables and functions */

__attribute__((used)) static void InjectBytePaddingBlock(BrotliEncoderState* s) {
  uint32_t seal = s->last_byte_;
  size_t seal_bits = s->last_byte_bits_;
  uint8_t* destination;
  s->last_byte_ = 0;
  s->last_byte_bits_ = 0;
  /* is_last = 0, data_nibbles = 11, reserved = 0, meta_nibbles = 00 */
  seal |= 0x6u << seal_bits;
  seal_bits += 6;
  /* If we have already created storage, then append to it.
     Storage is valid until next block is being compressed. */
  if (s->next_out_) {
    destination = s->next_out_ + s->available_out_;
  } else {
    destination = s->tiny_buf_.u8;
    s->next_out_ = destination;
  }
  destination[0] = (uint8_t)seal;
  if (seal_bits > 8) destination[1] = (uint8_t)(seal >> 8);
  s->available_out_ += (seal_bits + 7) >> 3;
}