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
typedef  int u_int32_t ;
struct au_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AU_CDC_REGSET ; 
 int AU_CDC_WROK ; 
 int /*<<< orphan*/  AU_REG_CODECIO ; 
 int /*<<< orphan*/  AU_REG_CODECST ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int au_rd (struct au_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  au_wr (struct au_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int
au_wrcd(kobj_t obj, void *arg, int regno, u_int32_t data)
{
	struct au_info *au = (struct au_info *)arg;
	int i, j, tries;
	i=j=tries=0;
	do {
		while (j<50 && (i & AU_CDC_WROK) == 0) {
			i=au_rd(au, 0, AU_REG_CODECST, 4);
			DELAY(2000);
			j++;
		}
		if (j==50) printf("codec timeout during write of register %x, data %x\n",
				  regno, data);
		au_wr(au, 0, AU_REG_CODECIO, (regno<<16) | AU_CDC_REGSET | data, 4);
/*		DELAY(20000);
		i=au_rdcd(au, regno);
*/		tries++;
	} while (0); /* (i != data && tries < 3); */
	/*
	if (tries == 3) printf("giving up writing 0x%4x to codec reg %2x\n", data, regno);
	*/

	return 0;
}