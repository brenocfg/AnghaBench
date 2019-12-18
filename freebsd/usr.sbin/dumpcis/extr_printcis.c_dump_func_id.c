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
 int /*<<< orphan*/  printf (char*,char const*,char*,char*) ; 

__attribute__((used)) static void
dump_func_id(u_char *p)
{
	static const char *id[] = {
		"Multifunction card",
		"Memory card",
		"Serial port/modem",
		"Parallel port",
		"Fixed disk card",
		"Video adapter",
		"Network/LAN adapter",
		"AIMS",
		"SCSI card",
		"Security"
	};

	printf("\t%s%s%s\n",
	       (*p <= 9) ? id[*p] : "Unknown function",
	       (p[1] & 1) ? " - POST initialize" : "",
	       (p[1] & 2) ? " - Card has ROM" : "");
}