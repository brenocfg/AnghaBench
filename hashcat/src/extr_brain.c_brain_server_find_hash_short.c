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
typedef  int /*<<< orphan*/  u32 ;
typedef  int i64 ;
typedef  int /*<<< orphan*/  brain_server_hash_short_t ;

/* Variables and functions */
 int brain_server_sort_hash_short (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

i64 brain_server_find_hash_short (const u32 *search, const brain_server_hash_short_t *buf, const i64 cnt)
{
  for (i64 l = 0, r = cnt; r; r >>= 1)
  {
    const i64 m = r >> 1;
    const i64 c = l + m;

    const int cmp = brain_server_sort_hash_short (search, buf + c);

    if (cmp > 0)
    {
      l += m + 1;

      r--;
    }

    if (cmp == 0) return c;
  }

  return -1;
}