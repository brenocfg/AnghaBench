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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  _PNP_ADDRESS ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int rd_port ; 

u_char
pnp_read(int d)
{
    outb(_PNP_ADDRESS, d);
    return inb( (rd_port << 2) + 3) & 0xff;
}