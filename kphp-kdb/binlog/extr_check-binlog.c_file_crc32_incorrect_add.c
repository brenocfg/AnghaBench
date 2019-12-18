#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long long crc32_off; int /*<<< orphan*/  total_incorrect_crc32_logevents; } ;
typedef  TYPE_1__ file_t ;
struct TYPE_6__ {int incorrect_logevents; long long* last_incorrect_off; int found; } ;
typedef  TYPE_2__ crc32_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void file_crc32_incorrect_add (file_t *F, crc32_stat_t *S) {
  F->total_incorrect_crc32_logevents++;
  S->incorrect_logevents++;
  int i = S->incorrect_logevents & 3;
  S->last_incorrect_off[i] = F->crc32_off;
  if (S->incorrect_logevents >= 3) {
    long long s = S->last_incorrect_off[i] - S->last_incorrect_off[(i+2)&3];
    assert (s >= 0);
    S->found = s <= 0x20000;
  }
}