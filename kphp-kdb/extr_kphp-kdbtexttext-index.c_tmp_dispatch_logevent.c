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
 int /*<<< orphan*/  assert (int) ; 
 int conv_uid (int) ; 
 int* pass_min_uid ; 
 int passes ; 
 int /*<<< orphan*/ * temp_file ; 
 int /*<<< orphan*/  tmp_write_logevent (int /*<<< orphan*/ *,void const*,int) ; 

int tmp_dispatch_logevent (const void *L, int size) {
  assert (size >= 8);
  int user_id = ((int *) L)[1];
  int uid = conv_uid (user_id);
  if (uid < 0) {
    return 0;
  }
  int a = -1, b = passes, c;
  while (b - a > 1) {
    c = ((a + b) >> 1);
    if (pass_min_uid[c] <= uid) {
      a = c;
    } else {
      b = c;
    }
  }
  assert (a >= 0 && uid < pass_min_uid[b]);
  tmp_write_logevent (&temp_file[a], L, size);
  return 1;
}