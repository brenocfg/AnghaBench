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
 scalar_t__ Q_raw ; 
 struct counter* get_counter_f (long long,int /*<<< orphan*/ ) ; 
 int get_counter_versions_raw (char*,long long) ; 
 int load_counter (long long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int get_counter_versions (char *buffer, long long counter_id) {
  if (Q_raw) {
    return get_counter_versions_raw (buffer, counter_id);
  }
  char *ptr = buffer;
  struct counter *C = get_counter_f (counter_id, 0);
  while (C && ptr < buffer + 100000 && C->prev >= 0) {
    if (ptr > buffer) { *ptr++ = ','; }
    ptr += sprintf (ptr, "%d", C->created_at);
    C = C->prev;
  }
  if (ptr < buffer + 100000) {
    if (load_counter (counter_id, 0, 1) == -2) {
      return -2;
    }
    ptr = buffer;
    C = get_counter_f (counter_id, 0);
    while (C && ptr < buffer + 100000 && C->prev >= 0) {
      if (ptr > buffer) { *ptr++ = ','; }
      ptr += sprintf (ptr, "%d", C->created_at);
      C = C->prev;
    }
  }
  return ptr - buffer;
}