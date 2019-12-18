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
struct au_info {int unit; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AU_CDC_DATAMASK ; 
 int AU_CDC_REGMASK ; 
 int /*<<< orphan*/  AU_REG_CODECIO ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int au_rd (struct au_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  au_wr (struct au_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static int
au_rdcd(kobj_t obj, void *arg, int regno)
{
	struct au_info *au = (struct au_info *)arg;
	int i=0, j=0;

	regno<<=16;
	au_wr(au, 0, AU_REG_CODECIO, regno, 4);
	while (j<50) {
		i=au_rd(au, 0, AU_REG_CODECIO, 4);
		if ((i & 0x00ff0000) == (regno | 0x00800000)) break;
		DELAY(j * 200 + 2000);
		j++;
	}
	if (j==50) printf("pcm%d: codec timeout reading register %x (%x)\n",
		au->unit, (regno & AU_CDC_REGMASK)>>16, i);
	return i & AU_CDC_DATAMASK;
}