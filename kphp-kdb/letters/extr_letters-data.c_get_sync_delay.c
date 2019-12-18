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
 int MAX_PRIORITY ; 
 int now ; 
 int* sync_last ; 

int get_sync_delay (void) {
  int i;
  int res = 0;

  for (i = 0; i <= MAX_PRIORITY; i++) {
    if (now - sync_last[i] > res) {
      res = now - sync_last[i];
    }
  }
  return res;
}