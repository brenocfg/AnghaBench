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
#define  CMD_BKSP 133 
#define  CMD_CLR 132 
#define  CMD_CR 131 
#define  CMD_HOME 130 
#define  CMD_NL 129 
#define  CMD_RESET 128 
 int /*<<< orphan*/  HD_COMMAND ; 
 int /*<<< orphan*/  HD_DATA ; 
 int /*<<< orphan*/  debug (int,char*,int,char*,char*,char*) ; 
 int hd44780_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hd44780_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hd_blink ; 
 int /*<<< orphan*/  hd_cursor ; 
 int /*<<< orphan*/  hd_font ; 
 int hd_lines ; 
 int /*<<< orphan*/  isprint (int) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static void
hd44780_command(int cmd) 
{
    u_int8_t	val;

    switch (cmd) {
    case CMD_RESET:	/* full manual reset and reconfigure as per datasheet */
	debug(1, "hd44780: reset to %d lines, %s font,%s%s cursor", 
	      hd_lines, hd_font ? "5x10" : "5x7", hd_cursor ? "" : " no", hd_blink ? " blinking" : "");
	val = 0x30;
	if (hd_lines == 2)
	    val |= 0x08;
	if (hd_font)
	    val |= 0x04;
	hd44780_output(HD_COMMAND, val);
	usleep(10000);
	hd44780_output(HD_COMMAND, val);
	usleep(1000);
	hd44780_output(HD_COMMAND, val);
	usleep(1000);
	val = 0x08;				/* display off */
	hd44780_output(HD_COMMAND, val);
	usleep(1000);
	val |= 0x04;				/* display on */
	if (hd_cursor)
	    val |= 0x02;
	if (hd_blink)
	    val |= 0x01;
	hd44780_output(HD_COMMAND, val);
	usleep(1000);
	hd44780_output(HD_COMMAND, 0x06);	/* shift cursor by increment */
	usleep(1000);
	/* FALLTHROUGH */

    case CMD_CLR:
	hd44780_output(HD_COMMAND, 0x01);
	usleep(2000);
	break;

    case CMD_BKSP:
	hd44780_output(HD_DATA, 0x10);		/* shift cursor left one */
	break;
	
    case CMD_NL:
	if (hd_lines == 2)
	    hd44780_output(HD_COMMAND, 0xc0);	/* beginning of second line */
	break;
	
    case CMD_CR:
	/* XXX will not work in 4-line mode, or where readback fails */
	val = hd44780_input(HD_COMMAND) & 0x3f;	/* mask character position, save line pos */
	hd44780_output(HD_COMMAND, 0x80 | val);
	break;
	
    case CMD_HOME:
	hd44780_output(HD_COMMAND, 0x02);
	usleep(2000);
	break;
	
    default:
	if (isprint(cmd)) {
	    warnx("unknown command %c", cmd);
	} else {
	    warnx("unknown command 0x%x", cmd);
	}
    }
    usleep(40);
}