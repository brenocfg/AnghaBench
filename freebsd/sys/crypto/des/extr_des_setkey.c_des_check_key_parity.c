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
 int DES_KEY_SZ ; 
 unsigned char const* odd_parity ; 

int des_check_key_parity(const unsigned char *key)
{
	int i;

	for (i=0; i<DES_KEY_SZ; i++)
		{
		if (key[i] != odd_parity[key[i]])
			return(0);
		}
	return(1);
}