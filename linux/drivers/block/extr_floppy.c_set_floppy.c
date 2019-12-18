#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fd_device; } ;

/* Variables and functions */
 int ITYPE (int /*<<< orphan*/ ) ; 
 TYPE_1__* UDRS ; 
 scalar_t__ _floppy ; 
 scalar_t__* current_type ; 
 scalar_t__ floppy_type ; 

__attribute__((used)) static void set_floppy(int drive)
{
	int type = ITYPE(UDRS->fd_device);

	if (type)
		_floppy = floppy_type + type;
	else
		_floppy = current_type[drive];
}