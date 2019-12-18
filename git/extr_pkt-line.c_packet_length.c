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
 int hex2chr (char const*) ; 

__attribute__((used)) static int packet_length(const char *linelen)
{
	int val = hex2chr(linelen);
	return (val < 0) ? val : (val << 8) | hex2chr(linelen + 2);
}