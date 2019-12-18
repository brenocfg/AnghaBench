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
 int ALPH_N ; 
 double** prob ; 

void process_errors (char *errors[ALPH_N], double pr) {
  int i, j;
  for (i = 0; i < ALPH_N; i++) {
    int A = (unsigned char)errors[i][0] % 224;
    for (j = 1; errors[i][j]; j++)
      prob[A][(unsigned char)errors[i][j] % 224] = pr;
  }
}