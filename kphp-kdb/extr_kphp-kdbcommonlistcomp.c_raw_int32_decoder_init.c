#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int prefix_bit_offset; int /*<<< orphan*/  ptr; } ;
struct list_decoder {int /*<<< orphan*/ * decode_int; TYPE_1__ br; scalar_t__ k; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  raw_int32_decode_int ; 

__attribute__((used)) static void raw_int32_decoder_init (struct list_decoder *dec) {
  assert (!(dec->br.prefix_bit_offset & 7));
  dec->k = 0;
  dec->br.ptr--;
  dec->decode_int = &raw_int32_decode_int;
}