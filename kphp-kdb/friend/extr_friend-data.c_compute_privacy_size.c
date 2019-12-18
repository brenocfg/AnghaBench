#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int y; int* List; } ;
typedef  TYPE_1__ privacy_t ;

/* Variables and functions */

__attribute__((used)) static int compute_privacy_size (privacy_t *T) {
  int t = T->y & 255;
  return sizeof(privacy_t) + 4*(t == 255 ? T->List[0]+1 : t) + 4;
}