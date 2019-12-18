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

/* Variables and functions */
 int /*<<< orphan*/  AU_REG_ADB ; 
 int au_rd (struct au_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  au_wr (struct au_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
au_setadb(struct au_info *au, u_int32_t c, u_int32_t enable)
{
	int x;

	x = au_rd(au, 0, AU_REG_ADB, 4);
	x &= ~(1 << c);
	x |= (enable << c);
	au_wr(au, 0, AU_REG_ADB, x, 4);
}