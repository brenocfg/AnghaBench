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
struct html {int dummy; } ;

/* Variables and functions */
#define  ASCII_BREAK 130 
#define  ASCII_HYPH 129 
#define  ASCII_NBRSP 128 
 int /*<<< orphan*/  print_byte (struct html*,char) ; 
 int /*<<< orphan*/  print_word (struct html*,char*) ; 

__attribute__((used)) static int
print_escape(struct html *h, char c)
{

	switch (c) {
	case '<':
		print_word(h, "&lt;");
		break;
	case '>':
		print_word(h, "&gt;");
		break;
	case '&':
		print_word(h, "&amp;");
		break;
	case '"':
		print_word(h, "&quot;");
		break;
	case ASCII_NBRSP:
		print_word(h, "&nbsp;");
		break;
	case ASCII_HYPH:
		print_byte(h, '-');
		break;
	case ASCII_BREAK:
		break;
	default:
		return 0;
	}
	return 1;
}