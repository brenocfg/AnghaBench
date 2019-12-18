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
typedef  size_t u32 ;
struct TYPE_2__ {size_t dgst_pos0; size_t dgst_pos1; size_t dgst_pos2; size_t dgst_pos3; } ;
typedef  TYPE_1__ hashconfig_t ;

/* Variables and functions */

int sort_by_digest_p0p1 (const void *v1, const void *v2, void *v3)
{
  const u32 *d1 = (const u32 *) v1;
  const u32 *d2 = (const u32 *) v2;

  hashconfig_t *hashconfig = (hashconfig_t *) v3;

  const u32 dgst_pos0 = hashconfig->dgst_pos0;
  const u32 dgst_pos1 = hashconfig->dgst_pos1;
  const u32 dgst_pos2 = hashconfig->dgst_pos2;
  const u32 dgst_pos3 = hashconfig->dgst_pos3;

  if (d1[dgst_pos3] > d2[dgst_pos3]) return  1;
  if (d1[dgst_pos3] < d2[dgst_pos3]) return -1;
  if (d1[dgst_pos2] > d2[dgst_pos2]) return  1;
  if (d1[dgst_pos2] < d2[dgst_pos2]) return -1;
  if (d1[dgst_pos1] > d2[dgst_pos1]) return  1;
  if (d1[dgst_pos1] < d2[dgst_pos1]) return -1;
  if (d1[dgst_pos0] > d2[dgst_pos0]) return  1;
  if (d1[dgst_pos0] < d2[dgst_pos0]) return -1;

  return 0;
}