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
struct gather {TYPE_1__* List; } ;
struct TYPE_2__ {int bytes; } ;

/* Variables and functions */

void default_gather_on_error (struct gather *G, int num) {
  G->List[num].bytes = -3;
}