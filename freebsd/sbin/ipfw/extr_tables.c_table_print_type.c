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
typedef  int uint8_t ;

/* Variables and functions */
#define  IPFW_TABLE_FLOW 128 
 int /*<<< orphan*/  flowtypecmds ; 
 char* match_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_flags_buffer (char*,size_t,int /*<<< orphan*/ ,int) ; 
 int snprintf (char*,size_t,char*,char const*) ; 
 int /*<<< orphan*/  tabletypes ; 

void
table_print_type(char *tbuf, size_t size, uint8_t type, uint8_t tflags)
{
	const char *tname;
	int l;

	if ((tname = match_value(tabletypes, type)) == NULL)
		tname = "unknown";

	l = snprintf(tbuf, size, "%s", tname);
	tbuf += l;
	size -= l;

	switch(type) {
	case IPFW_TABLE_FLOW:
		if (tflags != 0) {
			*tbuf++ = ':';
			l--;
			print_flags_buffer(tbuf, size, flowtypecmds, tflags);
		}
		break;
	}
}