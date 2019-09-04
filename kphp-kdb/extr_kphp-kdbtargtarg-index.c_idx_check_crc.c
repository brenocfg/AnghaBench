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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idx_cur_read_pos () ; 
 char* idx_filename ; 
 unsigned int idx_relax_crc32 () ; 
 scalar_t__ readin_int () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static inline void idx_check_crc (void) {
  unsigned crc32 = idx_relax_crc32 ();
  if ((unsigned) readin_int() != crc32) {
    fprintf (stderr, "crc32 mismatch while reading snapshot %s at position %lld\n", idx_filename, idx_cur_read_pos ());
    assert (0);
  }
}