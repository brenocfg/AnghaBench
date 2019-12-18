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
typedef  int ui64 ;

/* Variables and functions */
 int get_tcb_bit (unsigned char*,int) ; 

__attribute__((used)) static ui64
get_tcb_bits (unsigned char  *A, int hi, int lo)
{
  ui64 ret=0;

  if (lo>hi) {
    int temp=lo;
    lo=hi;
    hi=temp;
  }

  while (hi>=lo) {
    ret = (ret<<1) | get_tcb_bit(A,hi);
    --hi;
  }
  
  return ret;
}