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
typedef  int u32 ;
struct tpm_chip {int nr_commands; int* cc_attrs_tbl; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 

int tpm2_find_cc(struct tpm_chip *chip, u32 cc)
{
	int i;

	for (i = 0; i < chip->nr_commands; i++)
		if (cc == (chip->cc_attrs_tbl[i] & GENMASK(15, 0)))
			return i;

	return -1;
}