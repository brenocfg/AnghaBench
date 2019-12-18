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
typedef  int /*<<< orphan*/  u8 ;
struct macio_chip {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACIO_OUT8 (long,int /*<<< orphan*/ ) ; 
 struct macio_chip* macio_chips ; 

__attribute__((used)) static long
core99_write_gpio(struct device_node *node, long param, long value)
{
	struct macio_chip *macio = &macio_chips[0];

	MACIO_OUT8(param, (u8)(value & 0xff));
	return 0;
}