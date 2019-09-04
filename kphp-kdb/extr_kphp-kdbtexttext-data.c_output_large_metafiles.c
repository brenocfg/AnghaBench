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
 int LN ; 
 int* LX ; 
 int* LY ; 
 int* LZ ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

void output_large_metafiles (void) {
  int i;
  for (i = 1; i <= LN; i++) {
    if (LX[i]) {
      printf ("%d\t%d\t%d\n", LX[i], LY[i], LZ[i]);
    }
  }
}