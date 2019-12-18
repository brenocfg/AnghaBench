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
 int conv_rus_utf8 (int const) ; 
 int stem_rus (int,int*) ; 
 int* stem_ts ; 

int stem_rus_utf8i (const int *v, int *delete_penultimate_letter) {
  int i;
  for (i = 0; v[i]; i++) {
    stem_ts[i] = conv_rus_utf8 (v[i]);
  }
  stem_ts[i] = -1;
  return stem_rus (i, delete_penultimate_letter);
}