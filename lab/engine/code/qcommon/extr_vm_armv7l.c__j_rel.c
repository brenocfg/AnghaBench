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
 int /*<<< orphan*/  DIE (char*,int,int) ; 

__attribute__((used)) static inline unsigned _j_rel(int x, int pc)
{
	if (x&3) goto err;
	x = (x>>2)-2;
	if (x < 0)
	{
		if ((x&(0xFF<<24)) != 0xFF<<24)
			goto err;
		x &= ~(0xFF<<24);
	}
	else if (x&(0xFF<<24))
		goto err;
	return x;
err:
	DIE("jump %d out of range at %d", x, pc);
}