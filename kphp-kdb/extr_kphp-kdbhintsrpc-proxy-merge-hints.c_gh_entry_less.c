#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rating; scalar_t__ type; scalar_t__ object_id; } ;
typedef  TYPE_1__ gh_entry_t ;

/* Variables and functions */

__attribute__((used)) static inline int gh_entry_less (gh_entry_t *lhs, gh_entry_t *rhs) {
  return (lhs->rating > rhs->rating + 1e-9 || (lhs->rating >= rhs->rating - 1e-9 && 
          (lhs->type  < rhs->type          || (lhs->type   == rhs->type && lhs->object_id < rhs->object_id))));
}