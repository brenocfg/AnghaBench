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
 scalar_t__ isdigit (unsigned char) ; 
 char toupper (unsigned char) ; 

__attribute__((used)) static unsigned int hex2int(unsigned char c)
{
	return isdigit(c) ? c - '0' : toupper(c) - 'A' + 10;
}