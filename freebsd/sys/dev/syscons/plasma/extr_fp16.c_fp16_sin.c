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
typedef  int fp16_t ;

/* Variables and functions */
 int FP16_2PI ; 
 int* fp16_sin_table ; 

fp16_t
fp16_sin(fp16_t theta)
{
	unsigned int i;

	i = 1024 * (theta % FP16_2PI) / FP16_2PI;
	switch (i / 256) {
	case 0:
		return (fp16_sin_table[i % 256]);
	case 1:
		return (fp16_sin_table[255 - i % 256]);
	case 2:
		return (-fp16_sin_table[i % 256]);
	case 3:
		return (-fp16_sin_table[255 - i % 256]);
	default:
		/* inconceivable! */
		return (0);
	}
}