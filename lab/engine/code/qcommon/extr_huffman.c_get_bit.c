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
typedef  int byte ;

/* Variables and functions */
 int bloc ; 

__attribute__((used)) static int get_bit (byte *fin) {
	int t;
	t = (fin[(bloc>>3)] >> (bloc&7)) & 0x1;
	bloc++;
	return t;
}