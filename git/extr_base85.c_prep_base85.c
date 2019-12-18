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
 int ARRAY_SIZE (int*) ; 
 int* de85 ; 
 int* en85 ; 

__attribute__((used)) static void prep_base85(void)
{
	int i;
	if (de85['Z'])
		return;
	for (i = 0; i < ARRAY_SIZE(en85); i++) {
		int ch = en85[i];
		de85[ch] = i + 1;
	}
}