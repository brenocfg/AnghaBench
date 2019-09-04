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
 int /*<<< orphan*/  TL_MAYBE_FALSE ; 
 int /*<<< orphan*/  TL_MAYBE_TRUE ; 
 struct counter* get_counter_old (long long,int,int) ; 
 int /*<<< orphan*/  tl_serialize_counter (struct counter*,int) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 

int tl_get_counter_serialized (long long counter_id, int version, int mode) {
  struct counter *C = get_counter_old (counter_id, version, 1);
  if (!C) { 
    tl_store_int (TL_MAYBE_FALSE);
    return 0;
  }
  if (C->type == -2) { return -2; }
  tl_store_int (TL_MAYBE_TRUE);
  tl_serialize_counter (C, mode);
  return 0;
}