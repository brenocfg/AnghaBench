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
 int addi (long,long,long,long,int) ; 

__attribute__((used)) static int subi(long x, long y, long min, long max, int needconst) {
	return addi(x, -y, min, max, needconst);
}