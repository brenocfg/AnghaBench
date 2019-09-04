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
struct TYPE_3__ {int /*<<< orphan*/  action; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ recommend_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_recommend_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static inline double recommend_item_get_rate (recommend_item_t *p) {
  double rate;
  if (!get_recommend_rate (p->type, p->action, &rate)) {
    return rate;
  }
  return 1.0;
}