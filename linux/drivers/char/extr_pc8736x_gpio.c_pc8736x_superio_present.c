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
 int SIO_BASE1 ; 
 int SIO_BASE2 ; 
 int /*<<< orphan*/  SIO_SID ; 
 int SIO_SID_PC87365 ; 
 int SIO_SID_PC87366 ; 
 int superio_cmd ; 
 int superio_inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pc8736x_superio_present(void)
{
	int id;

	/* try the 2 possible values, read a hardware reg to verify */
	superio_cmd = SIO_BASE1;
	id = superio_inb(SIO_SID);
	if (id == SIO_SID_PC87365 || id == SIO_SID_PC87366)
		return superio_cmd;

	superio_cmd = SIO_BASE2;
	id = superio_inb(SIO_SID);
	if (id == SIO_SID_PC87365 || id == SIO_SID_PC87366)
		return superio_cmd;

	return 0;
}