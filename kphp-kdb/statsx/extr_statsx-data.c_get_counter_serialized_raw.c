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
struct counter {int type; } ;

/* Variables and functions */
 int counter_serialize_raw (struct counter*,char*) ; 
 struct counter* get_counter_old (long long,int,int) ; 

int get_counter_serialized_raw (char *buffer, long long counter_id, int version) {
//  int *ptr = (int *)buffer;
  struct counter *C = get_counter_old (counter_id, version, 1);
  if (!C) { return 0; }
  if (C->type == -2) return -2;
  return counter_serialize_raw (C, buffer);
}