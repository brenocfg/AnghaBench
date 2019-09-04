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
typedef  size_t u32 ;

/* Variables and functions */

__attribute__((used)) static void selftest_to_bitmap (const u32 dgst_shifts, char *digests_buf_ptr, const u32 dgst_pos0, const u32 dgst_pos1, const u32 dgst_pos2, const u32 dgst_pos3, const u32 bitmap_mask, u32 *bitmap_a, u32 *bitmap_b, u32 *bitmap_c, u32 *bitmap_d)
{
  u32 *digest_ptr = (u32 *) digests_buf_ptr;

  const u32 val0 = 1u << (digest_ptr[dgst_pos0] & 0x1f);
  const u32 val1 = 1u << (digest_ptr[dgst_pos1] & 0x1f);
  const u32 val2 = 1u << (digest_ptr[dgst_pos2] & 0x1f);
  const u32 val3 = 1u << (digest_ptr[dgst_pos3] & 0x1f);

  const u32 idx0 = (digest_ptr[dgst_pos0] >> dgst_shifts) & bitmap_mask;
  const u32 idx1 = (digest_ptr[dgst_pos1] >> dgst_shifts) & bitmap_mask;
  const u32 idx2 = (digest_ptr[dgst_pos2] >> dgst_shifts) & bitmap_mask;
  const u32 idx3 = (digest_ptr[dgst_pos3] >> dgst_shifts) & bitmap_mask;

  bitmap_a[idx0] |= val0;
  bitmap_b[idx1] |= val1;
  bitmap_c[idx2] |= val2;
  bitmap_d[idx3] |= val3;
}