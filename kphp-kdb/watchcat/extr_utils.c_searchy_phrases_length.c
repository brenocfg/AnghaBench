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
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ searchy_query_phrase_t ;

/* Variables and functions */

int searchy_phrases_length (searchy_query_phrase_t *cur) {
  int res = 0;
  while (cur != NULL) {
    res++;
    cur = cur->next;
  }
  return res;
}