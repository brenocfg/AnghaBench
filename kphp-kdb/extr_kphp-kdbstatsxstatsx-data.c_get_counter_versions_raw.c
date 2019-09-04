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
struct counter {struct counter* prev; int /*<<< orphan*/  created_at; } ;

/* Variables and functions */
 struct counter* get_counter_f (long long,int /*<<< orphan*/ ) ; 
 int load_counter (long long,int /*<<< orphan*/ ,int) ; 

int get_counter_versions_raw (char *buffer, long long counter_id) {
  int *ptr = (int *)buffer;
  struct counter *C = get_counter_f (counter_id, 0);
  while (C && ptr < (int *)(buffer + 100000) && C->prev >= 0) {
    *(ptr++) = C->created_at;
    C = C->prev;
  }
  if (ptr < (int *)(buffer + 100000)) {
    if (load_counter (counter_id, 0, 1) == -2) {
      return -2;
    }
    ptr = (int *)buffer;
    C = get_counter_f (counter_id, 0);
    while (C && ptr < (int *)(buffer + 100000) && C->prev >= 0) {
      *(ptr++) = C->created_at;
      C = C->prev;
    }
  }
  return ((char *)ptr) - buffer;
}