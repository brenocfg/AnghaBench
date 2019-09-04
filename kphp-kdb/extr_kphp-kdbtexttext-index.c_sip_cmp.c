#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct search_index_pair {scalar_t__ crc; scalar_t__ idx; } ;

/* Variables and functions */

__attribute__((used)) static inline int sip_cmp (struct search_index_pair *a, struct search_index_pair *b) {
  if (a->crc < b->crc) {
    return -1;
  } else if (a->crc > b->crc) {
    return 1;
  } else if (a->idx < b->idx) {
    return -1;
  } else if (a->idx > b->idx) {
    return 1;
  }
  return 0;
}