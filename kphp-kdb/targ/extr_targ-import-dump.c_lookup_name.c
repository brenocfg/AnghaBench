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
 int MAX_GID ; 

char *lookup_name (char *D, int DL, int id, int *len, int max_len) {
  *len = 0;
  if (!D || DL < MAX_GID * 4 || id <= 0 || id >= MAX_GID) {
    return 0;
  }
  int x = ((int *) D)[id];
  if (x < MAX_GID * 4 || x + 4 > DL) {
    return 0;
  }
  int l = *((int *) (D + x));
  if ((unsigned) l > (unsigned) max_len || x + l + 5 > DL) {
    return 0;
  }
  *len = l;
  return D + x + 4;
}