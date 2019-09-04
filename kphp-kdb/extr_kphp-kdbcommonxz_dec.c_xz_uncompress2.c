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
struct xz_dec {int dummy; } ;
struct xz_buf {int in_size; int out_pos; int out_size; void* out; scalar_t__ in_pos; void* in; } ;
typedef  enum xz_ret { ____Placeholder_xz_ret } xz_ret ;

/* Variables and functions */
 int /*<<< orphan*/  XZ_SINGLE ; 
 int XZ_STREAM_END ; 
 int /*<<< orphan*/  xz_dec_end (struct xz_dec*) ; 
 struct xz_dec* xz_dec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xz_dec_run (struct xz_dec*,struct xz_buf*) ; 

int xz_uncompress2 (void *dst, int *dest_len, void *src, int src_len) {
  struct xz_dec *D = xz_dec_init (XZ_SINGLE, 0);
  if (D == NULL) {
    return -1;
  }
  struct xz_buf b;
  b.in = src;
  b.in_pos = 0;
  b.in_size = src_len;
  b.out = dst;
  b.out_pos = 0;
  b.out_size = *dest_len;
  enum xz_ret r = xz_dec_run (D, &b);
  xz_dec_end (D);
  if (r != XZ_STREAM_END) {
    return -1;
  }
  *dest_len = b.out_pos;
  return 0;
}