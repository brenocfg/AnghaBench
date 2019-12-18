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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int canny_ringbuffer_allocation; } ;
typedef  TYPE_1__ BrotliDecoderState ;
typedef  int BrotliDecoderParameter ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
#define  BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION 128 
 int /*<<< orphan*/  BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 

BROTLI_BOOL BrotliDecoderSetParameter(
    BrotliDecoderState* state, BrotliDecoderParameter p, uint32_t value) {
  switch (p) {
    case BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION:
      state->canny_ringbuffer_allocation = !!value ? 0 : 1;
      return BROTLI_TRUE;

    default: return BROTLI_FALSE;
  }
}