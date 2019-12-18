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
struct TYPE_2__ {long long x; } ;

/* Variables and functions */
 scalar_t__ MAX_DIFF ; 
 TYPE_1__* to_del ; 
 scalar_t__ to_del_n ; 
 int /*<<< orphan*/  to_del_overflow ; 

inline int insert_to_del (long long x) {
  if (to_del_n < MAX_DIFF) {
    to_del[to_del_n++].x = x;
    return 1;
  } else {
    to_del_overflow++;
    return 0;
  }
}