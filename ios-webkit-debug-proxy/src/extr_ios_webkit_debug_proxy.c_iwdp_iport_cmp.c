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
typedef  TYPE_1__* iwdp_iport_t ;
struct TYPE_2__ {scalar_t__ port; } ;

/* Variables and functions */

int iwdp_iport_cmp(const void *a, const void *b) {
  const iwdp_iport_t ipa = *((iwdp_iport_t *)a);
  const iwdp_iport_t ipb = *((iwdp_iport_t *)b);
  if (ipa == ipb || !ipa || !ipb) {
    return (ipa == ipb ? 0 : ipa ? -1 : 1);
  }
  uint32_t pa = ipa->port;
  uint32_t pb = ipb->port;
  return (pa == pb ? 0 : pa < pb ? -1 : 1);
}