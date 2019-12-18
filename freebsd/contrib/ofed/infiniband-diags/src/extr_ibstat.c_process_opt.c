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
 int /*<<< orphan*/  list_only ; 
 int /*<<< orphan*/  list_ports ; 
 int /*<<< orphan*/  short_format ; 

__attribute__((used)) static int process_opt(void *context, int ch, char *optarg)
{
	switch (ch) {
	case 'l':
		list_only++;
		break;
	case 's':
		short_format++;
		break;
	case 'p':
		list_ports++;
		break;
	default:
		return -1;
	}
	return 0;
}