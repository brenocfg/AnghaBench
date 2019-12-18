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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,char const*,char*) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
usb_quirk_strtou16(const char **pptr, const char *name, const char *what)
{
	unsigned long value;
	char *end;

	value = strtoul(*pptr, &end, 0);
	if (value > 65535 || *pptr == end || (*end != ' ' && *end != '\t')) {
		printf("%s: %s 16-bit %s value set to zero\n",
		    name, what, *end == 0 ? "incomplete" : "invalid");
		return (0);
	}
	*pptr = end + 1;
	return ((uint16_t)value);
}