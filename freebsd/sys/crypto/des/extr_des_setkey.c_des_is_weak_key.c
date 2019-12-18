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
typedef  int /*<<< orphan*/  des_cblock ;

/* Variables and functions */
 int NUM_WEAK_KEY ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/ * weak_keys ; 

int des_is_weak_key(const unsigned char *key)
{
	int i;

	for (i=0; i<NUM_WEAK_KEY; i++)
		/* Added == 0 to comparison, I obviously don't run
		 * this section very often :-(, thanks to
		 * engineering@MorningStar.Com for the fix
		 * eay 93/06/29
		 * Another problem, I was comparing only the first 4
		 * bytes, 97/03/18 */
		if (memcmp(weak_keys[i],key,sizeof(des_cblock)) == 0) return(1);
	return(0);
}