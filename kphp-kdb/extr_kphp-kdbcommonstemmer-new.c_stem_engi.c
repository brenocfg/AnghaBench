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
 int conv_eng (int) ; 
 int do_stem_eng (int) ; 
 int last_letter ; 
 int maxn ; 
 int* stem_ts ; 

int stem_engi (int *v) {
  int n;
  for (n = 0; v[n] && n + 1 < maxn; n++) {
    stem_ts[n] = conv_eng (v[n]);
  }
  stem_ts[n] = -1;

  int len2 = do_stem_eng (n);
  if (last_letter && len2 > 0) {
    v[len2 - 1] = last_letter;
  }
  v[len2] = 0;
  return len2;
}