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
typedef  int /*<<< orphan*/  olist_t ;
struct TYPE_2__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; } ;

/* Variables and functions */
 TYPE_1__* OHead ; 
 int OLIST_COUNT ; 

__attribute__((used)) static inline void online_list_init () {
  int i;
  for (i = 0; i < OLIST_COUNT; i++) {
    OHead[i].first = OHead[i].last = (olist_t *)&OHead[i];
  }
}