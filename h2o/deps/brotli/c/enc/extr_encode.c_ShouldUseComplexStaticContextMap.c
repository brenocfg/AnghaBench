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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 int /*<<< orphan*/  BROTLI_UNUSED (int) ; 
 int /*<<< orphan*/  CONTEXT_UTF8 ; 
 size_t Context (int,int,int /*<<< orphan*/ ) ; 
 double ShannonEntropy (int*,int,size_t*) ; 

__attribute__((used)) static BROTLI_BOOL ShouldUseComplexStaticContextMap(const uint8_t* input,
    size_t start_pos, size_t length, size_t mask, int quality, size_t size_hint,
    size_t* num_literal_contexts, const uint32_t** literal_context_map) {
  static const uint32_t kStaticContextMapComplexUTF8[64] = {
    11, 11, 12, 12, /* 0 special */
    0, 0, 0, 0, /* 4 lf */
    1, 1, 9, 9, /* 8 space */
    2, 2, 2, 2, /* !, first after space/lf and after something else. */
    1, 1, 1, 1, /* " */
    8, 3, 3, 3, /* % */
    1, 1, 1, 1, /* ({[ */
    2, 2, 2, 2, /* }]) */
    8, 4, 4, 4, /* :; */
    8, 7, 4, 4, /* . */
    8, 0, 0, 0, /* > */
    3, 3, 3, 3, /* [0..9] */
    5, 5, 10, 5, /* [A-Z] */
    5, 5, 10, 5,
    6, 6, 6, 6, /* [a-z] */
    6, 6, 6, 6,
  };
  BROTLI_UNUSED(quality);
  /* Try the more complex static context map only for long data. */
  if (size_hint < (1 << 20)) {
    return BROTLI_FALSE;
  } else {
    const size_t end_pos = start_pos + length;
    /* To make entropy calculations faster and to fit on the stack, we collect
       histograms over the 5 most significant bits of literals. One histogram
       without context and 13 additional histograms for each context value. */
    uint32_t combined_histo[32] = { 0 };
    uint32_t context_histo[13][32] = { { 0 } };
    uint32_t total = 0;
    double entropy[3];
    size_t dummy;
    size_t i;
    for (; start_pos + 64 <= end_pos; start_pos += 4096) {
      const size_t stride_end_pos = start_pos + 64;
      uint8_t prev2 = input[start_pos & mask];
      uint8_t prev1 = input[(start_pos + 1) & mask];
      size_t pos;
      /* To make the analysis of the data faster we only examine 64 byte long
         strides at every 4kB intervals. */
      for (pos = start_pos + 2; pos < stride_end_pos; ++pos) {
        const uint8_t literal = input[pos & mask];
        const uint8_t context = (uint8_t)kStaticContextMapComplexUTF8[
            Context(prev1, prev2, CONTEXT_UTF8)];
        ++total;
        ++combined_histo[literal >> 3];
        ++context_histo[context][literal >> 3];
        prev2 = prev1;
        prev1 = literal;
      }
    }
    entropy[1] = ShannonEntropy(combined_histo, 32, &dummy);
    entropy[2] = 0;
    for (i = 0; i < 13; ++i) {
      entropy[2] += ShannonEntropy(&context_histo[i][0], 32, &dummy);
    }
    entropy[0] = 1.0 / (double)total;
    entropy[1] *= entropy[0];
    entropy[2] *= entropy[0];
    /* The triggering heuristics below were tuned by compressing the individual
       files of the silesia corpus. If we skip this kind of context modeling
       for not very well compressible input (i.e. entropy using context modeling
       is 60% of maximal entropy) or if expected savings by symbol are less
       than 0.2 bits, then in every case when it triggers, the final compression
       ratio is improved. Note however that this heuristics might be too strict
       for some cases and could be tuned further. */
    if (entropy[2] > 3.0 || entropy[1] - entropy[2] < 0.2) {
      return BROTLI_FALSE;
    } else {
      *num_literal_contexts = 13;
      *literal_context_map = kStaticContextMapComplexUTF8;
      return BROTLI_TRUE;
    }
  }
}