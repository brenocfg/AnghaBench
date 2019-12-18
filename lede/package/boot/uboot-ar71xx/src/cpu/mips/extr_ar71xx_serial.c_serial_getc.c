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
 int /*<<< orphan*/  OFS_RCV_BUFFER ; 
 int UART16550_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_tstc () ; 

int serial_getc(void)
{
    while(!serial_tstc());

    return UART16550_READ(OFS_RCV_BUFFER);
}