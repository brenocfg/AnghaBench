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
typedef  int u_int8_t ;

/* Variables and functions */
 int HD_COMMAND ; 
 int HD_READ ; 
 int STROBE ; 
 int /*<<< orphan*/  debug (int,char*,int,char*) ; 
 int /*<<< orphan*/  hd_gdata (int) ; 
 int /*<<< orphan*/  hd_sctrl (int) ; 

__attribute__((used)) static int
hd44780_input(int type) 
{
    u_int8_t	val;

    hd_sctrl(type | HD_READ | STROBE);	/* set direction, address */ 
    hd_sctrl(type | HD_READ);		/* raise E */
    hd_gdata(val);			/* read data */
    hd_sctrl(type | HD_READ | STROBE);	/* lower E */

    debug(3, "0x%02x -> %s", val, (type == HD_COMMAND) ? "cmd " : "data");
    return(val);
}