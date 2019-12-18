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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ChooseContextMap (int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/  const**) ; 
 int MIN_QUALITY_FOR_CONTEXT_MODELING ; 
 scalar_t__ ShouldUseComplexStaticContextMap (int const*,size_t,size_t,size_t,int,size_t,size_t*,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static void DecideOverLiteralContextModeling(const uint8_t* input,
    size_t start_pos, size_t length, size_t mask, int quality, size_t size_hint,
    size_t* num_literal_contexts, const uint32_t** literal_context_map) {
  if (quality < MIN_QUALITY_FOR_CONTEXT_MODELING || length < 64) {
    return;
  } else if (ShouldUseComplexStaticContextMap(
      input, start_pos, length, mask, quality, size_hint,
      num_literal_contexts, literal_context_map)) {
    /* Context map was already set, nothing else to do. */
  } else {
    /* Gather bi-gram data of the UTF8 byte prefixes. To make the analysis of
       UTF8 data faster we only examine 64 byte long strides at every 4kB
       intervals. */
    const size_t end_pos = start_pos + length;
    uint32_t bigram_prefix_histo[9] = { 0 };
    for (; start_pos + 64 <= end_pos; start_pos += 4096) {
      static const int lut[4] = { 0, 0, 1, 2 };
      const size_t stride_end_pos = start_pos + 64;
      int prev = lut[input[start_pos & mask] >> 6] * 3;
      size_t pos;
      for (pos = start_pos + 1; pos < stride_end_pos; ++pos) {
        const uint8_t literal = input[pos & mask];
        ++bigram_prefix_histo[prev + lut[literal >> 6]];
        prev = lut[literal >> 6] * 3;
      }
    }
    ChooseContextMap(quality, &bigram_prefix_histo[0], num_literal_contexts,
                     literal_context_map);
  }
}