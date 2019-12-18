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
struct TYPE_2__ {scalar_t__* compression_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 TYPE_1__ Header ; 
 int NCOMPRESSION_METHODS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ compression_speed ; 
 scalar_t__ cur_offs ; 
 scalar_t__* encoded_bytes ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 scalar_t__ get_compression_bytes (int) ; 
 double get_utime (int /*<<< orphan*/ ) ; 
 double interpolative_percent ; 
 int /*<<< orphan*/  kprintf (char*,int,...) ; 
 int le_interpolative_ext ; 
 char* list_get_compression_method_description (int) ; 
 int /*<<< orphan*/  lists_encoded ; 
 scalar_t__* max_encoded_list_size ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 double percent (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  search_encode_lists (int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 
 scalar_t__ word_index_offset ; 

void search_estimate_compression_method (int c[2]) {
  memset (c, 0, sizeof(int) * 2);
  if (compression_speed < 0) {
    c[0] = c[1] = le_interpolative_ext;
    return;
  }
  if (!compression_speed) {
    return;
  }

  int method;
  int methods[2];
  for (method = 0; method < NCOMPRESSION_METHODS; method++) {
    methods[0] = methods[1] = method;
    double t = -get_utime(CLOCK_MONOTONIC);
    assert (!get_compression_bytes (method));
    search_encode_lists (methods, 1);
    if ((cur_offs - word_index_offset) != get_compression_bytes (method)) {
      kprintf ("cur_offs - word_index_offset == %lld\n", cur_offs - word_index_offset);
      kprintf ("get_compression_bytes (%d) = %lld\n", method, get_compression_bytes (method));
      assert (0);
    }
    t += get_utime (CLOCK_MONOTONIC);
    if (verbosity > 0) {
      fprintf (stderr, "Compression method: %s, %lld(%.6lf%%) = %lld(%.6lf%%)+%lld(%.6lf%%) bytes in %d lists (%.6lf seconds).\nMax encoded list bytes = %d.\n",
      list_get_compression_method_description (method),
      get_compression_bytes (method), percent (get_compression_bytes (method), get_compression_bytes (0)),
      encoded_bytes[0], percent (encoded_bytes[0], Header.compression_bytes[0]),
      encoded_bytes[1], percent (encoded_bytes[1], Header.compression_bytes[1]),
      lists_encoded, t,
      (max_encoded_list_size[0] > max_encoded_list_size[1]) ? max_encoded_list_size[0] : max_encoded_list_size[1]);
    }

    if (method) {
      int k;
      for (k = 0; k < 2; k++) {
        double p = percent (encoded_bytes[k], Header.compression_bytes[c[k] * 2 + k]);
        switch (method) {
          case 1:
            if (p < 100.0) { c[k] = method; }
            break;
          case 2:
            if (p < interpolative_percent) { c[k] = method; }
            break;
        }
      }
    }
  }

  if (verbosity > 0) {
    fprintf (stderr, "Choose %s+%s coding.\n",
             list_get_compression_method_description (c[0]),
             list_get_compression_method_description (c[1]));
  }
  return;
}