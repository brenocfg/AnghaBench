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
typedef  int __uint8_t ;

/* Variables and functions */
 scalar_t__ isc0 (int) ; 
 scalar_t__ isc1 (int) ; 

__attribute__((used)) static __inline bool iscntl(__uint8_t x)
{

	return (isc0(x) || isc1(x) || x == 0x7f);
}