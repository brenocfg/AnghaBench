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
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* iwdp_ipage_t ;
struct TYPE_2__ {scalar_t__ page_num; } ;

/* Variables and functions */

int iwdp_ipage_cmp(const void *a, const void *b) {
  const iwdp_ipage_t ipa = *((iwdp_ipage_t *)a);
  const iwdp_ipage_t ipb = *((iwdp_ipage_t *)b);
  if (ipa == ipb || !ipa || !ipb) {
    return (ipa == ipb ? 0 : ipa ? -1 : 1);
  }
  uint32_t pna = ipa->page_num;
  uint32_t pnb = ipb->page_num;
  return (pna == pnb ? 0 : pna < pnb ? -1 : 1);
}