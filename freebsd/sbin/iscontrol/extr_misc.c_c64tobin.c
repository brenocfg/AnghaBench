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
 unsigned char* base64 ; 

__attribute__((used)) static __inline unsigned char
c64tobin(unsigned char c64)
{
     int	i;
     for(i = 0; i < 64; i++)
	  if(base64[i] == c64)
	       break;
     return i;
}