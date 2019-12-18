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
 int sprintf (char*,char*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static inline int my_ether_ntoa(unsigned char *ea, char *buf)
{
	return sprintf(buf, "%02x:%02x:%02x:%02x:%02x:%02x",
		ea[0], ea[1], ea[2], ea[3], ea[4], ea[5]);
}