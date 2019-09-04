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
struct TYPE_4__ {scalar_t__ owner_id; scalar_t__ topic_id; scalar_t__ voting_id; } ;
typedef  TYPE_1__ voting_t ;

/* Variables and functions */

__attribute__((used)) static inline int cmp_voting (voting_t *x, voting_t *y) {
  if (x->owner_id < y->owner_id) {
    return -1;
  } else if (x->owner_id > y->owner_id) {
    return 1;
  } else if (x->topic_id < y->topic_id) {
    return -1;
  } else if (x->topic_id > y->topic_id) {
    return 1;
  } else if (x->voting_id < y->voting_id) {
    return -1;
  } else if (x->voting_id > y->voting_id) {
    return 1;
  } else {
    return 0;
  }
}