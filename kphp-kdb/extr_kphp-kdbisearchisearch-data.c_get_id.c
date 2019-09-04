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
 long long H_MUL ; 
 int get_id_by_hash (long long) ; 

int get_id (int *v) {
  long long h = 0;
  int i;
  for (i = 0; v[i]; i++) {
    h = h * H_MUL + v[i];
  }

  return get_id_by_hash (h);
}