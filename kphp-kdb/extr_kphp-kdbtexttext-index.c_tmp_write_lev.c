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
struct buff_file {scalar_t__ wptr; scalar_t__ wend; int after_crc32; int /*<<< orphan*/  crc32; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crc32_partial (void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 
 int /*<<< orphan*/  tmp_flush_out (struct buff_file*) ; 

void tmp_write_lev (struct buff_file *T, const void *L, int size) {
  size = (size + 3) & -4;
  assert (!(size & (-0x100000)));
  if (T->wptr + size > T->wend) {
    tmp_flush_out (T);
    assert (T->wptr + size <= T->wend);
  }
  memcpy (T->wptr, L, size);
  T->wptr += size;
  T->after_crc32 += size;
  T->crc32 = crc32_partial (L, size, T->crc32);
}