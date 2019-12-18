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

/* Variables and functions */
 int /*<<< orphan*/  black_list_check (scalar_t__) ; 
 int get_id_by_hash (long long) ; 
 scalar_t__ lowest_rate ; 
 int /*<<< orphan*/ * mark ; 
 int* mistakes ; 
 int mistakes_cnt ; 
 scalar_t__* names ; 
 scalar_t__ names_buff ; 
 scalar_t__* ratings ; 

void update_answer_mistakes (long long h, int _diff, int _A, int _B) {
  int id = get_id_by_hash (h);
  if (!mark[id] && ratings[id] > lowest_rate && !black_list_check (names_buff + names[id])) {
    int j;
    for (j = 0; j < mistakes_cnt && id != mistakes[j]; j++) {
    }
    if (j == mistakes_cnt) {
      mistakes[mistakes_cnt++] = id;
    }
  }
}