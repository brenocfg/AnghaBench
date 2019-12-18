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

void
swizzle_tcb(unsigned char *buf)
{
  int i,j,k;

  for (i=0, j=128-16 ; i<j ; i+=16, j-=16) {
    unsigned char temp;
    for (k=0; k<16; ++k) {
      temp=buf[i+k];
      buf[i+k]=buf[j+k];
      buf[j+k]=temp;
    }
  }
}