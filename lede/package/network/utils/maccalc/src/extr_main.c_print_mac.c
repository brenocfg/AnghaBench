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
 int /*<<< orphan*/  printf (char*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static void print_mac(unsigned char *buf)
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
	       buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
}