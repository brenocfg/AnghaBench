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
typedef  int uint32_t ;
struct TYPE_4__ {int quality; int lgwin; int lgblock; int size_hint; int /*<<< orphan*/  disable_literal_context_modeling; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {TYPE_1__ params; scalar_t__ is_initialized_; } ;
typedef  TYPE_2__ BrotliEncoderState ;
typedef  int BrotliEncoderParameter ;
typedef  int /*<<< orphan*/  BrotliEncoderMode ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FALSE ; 
#define  BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING 133 
#define  BROTLI_PARAM_LGBLOCK 132 
#define  BROTLI_PARAM_LGWIN 131 
#define  BROTLI_PARAM_MODE 130 
#define  BROTLI_PARAM_QUALITY 129 
#define  BROTLI_PARAM_SIZE_HINT 128 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 int /*<<< orphan*/  TO_BROTLI_BOOL (int) ; 

BROTLI_BOOL BrotliEncoderSetParameter(
    BrotliEncoderState* state, BrotliEncoderParameter p, uint32_t value) {
  /* Changing parameters on the fly is not implemented yet. */
  if (state->is_initialized_) return BROTLI_FALSE;
  /* TODO: Validate/clamp parameters here. */
  switch (p) {
    case BROTLI_PARAM_MODE:
      state->params.mode = (BrotliEncoderMode)value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_QUALITY:
      state->params.quality = (int)value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_LGWIN:
      state->params.lgwin = (int)value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_LGBLOCK:
      state->params.lgblock = (int)value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING:
      if ((value != 0) && (value != 1)) return BROTLI_FALSE;
      state->params.disable_literal_context_modeling = TO_BROTLI_BOOL(!!value);
      return BROTLI_TRUE;

    case BROTLI_PARAM_SIZE_HINT:
      state->params.size_hint = value;
      return BROTLI_TRUE;

    default: return BROTLI_FALSE;
  }
}