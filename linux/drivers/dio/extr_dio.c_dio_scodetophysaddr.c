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
 unsigned long DIOII_BASE ; 
 int DIOII_DEVSIZE ; 
 int DIOII_SCBASE ; 
 unsigned long DIO_BASE ; 
 int DIO_DEVSIZE ; 
 scalar_t__ DIO_SCINHOLE (int) ; 
 int DIO_SCMAX ; 

unsigned long dio_scodetophysaddr(int scode)
{
        if (scode >= DIOII_SCBASE) {
                return (DIOII_BASE + (scode - 132) * DIOII_DEVSIZE);
        } else if (scode > DIO_SCMAX || scode < 0)
                return 0;
        else if (DIO_SCINHOLE(scode))
                return 0;

        return (DIO_BASE + scode * DIO_DEVSIZE);
}