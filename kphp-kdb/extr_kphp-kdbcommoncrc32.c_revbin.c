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
 unsigned int GROUP_SWAP (unsigned int,int,int) ; 
 unsigned int __builtin_bswap32 (unsigned int) ; 

__attribute__((used)) static unsigned revbin (unsigned x) {
  x = GROUP_SWAP(x,0x55555555U,1);
  x = GROUP_SWAP(x,0x33333333U,2);
  x = GROUP_SWAP(x,0x0f0f0f0fU,4);
  x = __builtin_bswap32 (x);
  return x;
}