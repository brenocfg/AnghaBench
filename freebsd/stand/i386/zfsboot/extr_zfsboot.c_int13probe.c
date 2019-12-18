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
struct TYPE_2__ {int addr; int eax; int edx; int ecx; int /*<<< orphan*/  efl; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int DRV_MASK ; 
 int /*<<< orphan*/  V86_CY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V86_FLAGS ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

__attribute__((used)) static int
int13probe(int drive)
{
    v86.ctl = V86_FLAGS;
    v86.addr = 0x13;
    v86.eax = 0x800;
    v86.edx = drive;
    v86int();
    
    if (!V86_CY(v86.efl) &&				/* carry clear */
	((v86.edx & 0xff) != (drive & DRV_MASK))) {	/* unit # OK */
	if ((v86.ecx & 0x3f) == 0) {			/* absurd sector size */
		return(0);				/* skip device */
	}
	return (1);
    }
    return(0);
}