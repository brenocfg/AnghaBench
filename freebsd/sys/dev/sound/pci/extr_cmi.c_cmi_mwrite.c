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
struct mpu401 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void
cmi_mwrite(struct mpu401 *arg, void *sc, int reg, unsigned char b)
{

	bus_space_write_1(0,0,0x330 + reg , b);
}