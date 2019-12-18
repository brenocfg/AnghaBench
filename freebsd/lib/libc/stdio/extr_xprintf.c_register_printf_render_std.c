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
 int /*<<< orphan*/  __printf_arginfo_errno ; 
 int /*<<< orphan*/  __printf_arginfo_hexdump ; 
 int /*<<< orphan*/  __printf_arginfo_quote ; 
 int /*<<< orphan*/  __printf_arginfo_time ; 
 int /*<<< orphan*/  __printf_arginfo_vis ; 
 int /*<<< orphan*/  __printf_render_errno ; 
 int /*<<< orphan*/  __printf_render_hexdump ; 
 int /*<<< orphan*/  __printf_render_quote ; 
 int /*<<< orphan*/  __printf_render_time ; 
 int /*<<< orphan*/  __printf_render_vis ; 
 int /*<<< orphan*/  register_printf_render (char const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
register_printf_render_std(const char *specs)
{

	for (; *specs != '\0'; specs++) {
		switch (*specs) {
		case 'H':
			register_printf_render(*specs,
			    __printf_render_hexdump,
			    __printf_arginfo_hexdump);
			break;
		case 'M':
			register_printf_render(*specs,
			    __printf_render_errno,
			    __printf_arginfo_errno);
			break;
		case 'Q':
			register_printf_render(*specs,
			    __printf_render_quote,
			    __printf_arginfo_quote);
			break;
		case 'T':
			register_printf_render(*specs,
			    __printf_render_time,
			    __printf_arginfo_time);
			break;
		case 'V':
			register_printf_render(*specs,
			    __printf_render_vis,
			    __printf_arginfo_vis);
			break;
		default:
			return (-1);
		}
	}
	return (0);
}