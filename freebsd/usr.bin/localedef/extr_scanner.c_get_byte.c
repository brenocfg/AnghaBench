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
 int EOF ; 
 int esc_char ; 
 int scan_dec_byte () ; 
 int scan_hex_byte () ; 
 int scan_oct_byte () ; 
 int scanc () ; 
 int /*<<< orphan*/  unscanc (int) ; 

__attribute__((used)) static int
get_byte(void)
{
	int	c;

	if ((c = scanc()) != esc_char) {
		unscanc(c);
		return (EOF);
	}
	c = scanc();

	switch (c) {
	case 'd':
	case 'D':
		return (scan_dec_byte());
	case 'x':
	case 'X':
		return (scan_hex_byte());
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		/* put the character back so we can get it */
		unscanc(c);
		return (scan_oct_byte());
	default:
		unscanc(c);
		unscanc(esc_char);
		return (EOF);
	}
}