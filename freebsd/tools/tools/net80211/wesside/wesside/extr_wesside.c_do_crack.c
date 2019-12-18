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
 int KEYLIMIT ; 
 int PTW_KEYHSBYTES ; 
 int PTW_computeKey (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int /*<<< orphan*/  ptw ; 
 int /*<<< orphan*/  save_key (unsigned char*,int) ; 

int do_crack(void)
{
	unsigned char key[PTW_KEYHSBYTES];

	if(PTW_computeKey(ptw, key, 13, KEYLIMIT) == 1) {
		save_key(key, 13);
		return 1;
	}
	if(PTW_computeKey(ptw, key, 5, KEYLIMIT/10) == 1) {
		save_key(key, 5);
		return 1;
	}

	return 0;
}