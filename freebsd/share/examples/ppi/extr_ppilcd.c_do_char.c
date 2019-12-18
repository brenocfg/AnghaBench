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
struct lcd_driver {int /*<<< orphan*/  (* l_putc ) (char) ;int /*<<< orphan*/  (* l_command ) (char) ;} ;

/* Variables and functions */
 char CMD_BKSP ; 
 char CMD_CLR ; 
 char CMD_CR ; 
 char CMD_HOME ; 
 char CMD_NL ; 
 char CMD_RESET ; 
 scalar_t__ isprint (char) ; 
 int /*<<< orphan*/  stub1 (char) ; 
 int /*<<< orphan*/  stub2 (char) ; 
 int /*<<< orphan*/  stub3 (char) ; 
 int /*<<< orphan*/  stub4 (char) ; 
 int /*<<< orphan*/  stub5 (char) ; 
 int /*<<< orphan*/  stub6 (char) ; 
 int /*<<< orphan*/  stub7 (char) ; 
 int /*<<< orphan*/  stub8 (char) ; 
 int /*<<< orphan*/  stub9 (char) ; 
 scalar_t__ vflag ; 

__attribute__((used)) static void
do_char(struct lcd_driver *driver, char ch)
{
    static int	esc = 0;
    
    if (esc) {
	switch(ch) {
	case 'b':
	    driver->l_command(CMD_BKSP);
	    break;
	case 'f':
	    driver->l_command(CMD_CLR);
	    break;
	case 'n':
	    driver->l_command(CMD_NL);
	    break;
	case 'r':
	    driver->l_command(CMD_CR);
	    break;
	case 'R':
	    driver->l_command(CMD_RESET);
	    break;
	case 'v':
	    driver->l_command(CMD_HOME);
	    break;
	case '\\':
	    driver->l_putc('\\');
	    break;
	default:
	    driver->l_command(ch);
	    break;
	}
	esc = 0;
    } else {
	if (ch == '\\') {
	    esc = 1;
	} else {
	    if (vflag || isprint(ch))
		driver->l_putc(ch);
	}
    }
}