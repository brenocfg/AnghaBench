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
 scalar_t__ AU_REG_FIFOBASE ; 
 int /*<<< orphan*/  au_wr (struct au_info*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
au_clrfifo(struct au_info *au, u_int32_t c)
{
	u_int32_t i;

	for (i=0; i<32; i++) au_wr(au, 0, AU_REG_FIFOBASE+(c<<7)+(i<<2), 0, 4);
}