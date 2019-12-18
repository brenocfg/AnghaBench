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
typedef  int u64 ;

/* Variables and functions */
 int AMR_RD_BIT ; 
 int AMR_WR_BIT ; 
 int IAMR_EX_BIT ; 
 int /*<<< orphan*/  is_pkey_enabled (int) ; 
 int pkeyshift (int) ; 
 int read_amr () ; 
 int read_iamr () ; 

__attribute__((used)) static bool pkey_access_permitted(int pkey, bool write, bool execute)
{
	int pkey_shift;
	u64 amr;

	if (!is_pkey_enabled(pkey))
		return true;

	pkey_shift = pkeyshift(pkey);
	if (execute && !(read_iamr() & (IAMR_EX_BIT << pkey_shift)))
		return true;

	amr = read_amr(); /* Delay reading amr until absolutely needed */
	return ((!write && !(amr & (AMR_RD_BIT << pkey_shift))) ||
		(write &&  !(amr & (AMR_WR_BIT << pkey_shift))));
}