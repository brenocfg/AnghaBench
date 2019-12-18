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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 size_t read (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static uint8_t *
get_value(char *val, size_t *datalen)
{
	static char buffer[16*1024];

	if (val != NULL) {
		*datalen = strlen(val);
		return ((uint8_t *)val);
	}
	/* Read from stdin */
	*datalen = sizeof(buffer);
	*datalen = read(0, buffer, *datalen);
	return ((uint8_t *)buffer);
}