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
 int bin2bcd (int) ; 

__attribute__((used)) static int
bin2bcd32(int bin)
{
	int out = 0;
	int tmp;

	tmp = bin % 100;
	out += bin2bcd(tmp) * 1;
	bin = bin / 100;

	tmp = bin % 100;
	out += bin2bcd(tmp) * 100;
	bin = bin / 100;

	tmp = bin % 100;
	out += bin2bcd(tmp) * 10000;

	return (out);
}