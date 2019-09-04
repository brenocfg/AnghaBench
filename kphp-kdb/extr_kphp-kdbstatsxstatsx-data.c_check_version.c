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
struct counter {int created_at; struct counter* prev; } ;

/* Variables and functions */
 struct counter* get_counter_f (long long,int /*<<< orphan*/ ) ; 

int check_version (long long counter_id, int version) {
  struct counter *C = get_counter_f (counter_id, 0);
  while (C) {
    if (C->created_at < version) { return 0; }
    if (C->created_at == version) { return 1; }
    C = C->prev;
  }
  return -1;
}