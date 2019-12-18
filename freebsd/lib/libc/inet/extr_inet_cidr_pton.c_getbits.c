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
 char* digits ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
getbits(const char *src, int ipv6) {
	int bits = 0;
	char *cp, ch;
	
	if (*src == '\0')			/*%< syntax */
		return (-2);
	do {
		ch = *src++;
		cp = strchr(digits, ch);
		if (cp == NULL)			/*%< syntax */
			return (-2);
		bits *= 10;
		bits += cp - digits;
		if (bits == 0 && *src != '\0')	/*%< no leading zeros */
			return (-2);
		if (bits > (ipv6 ? 128 : 32))	/*%< range error */
			return (-2);
	} while (*src != '\0');

	return (bits);
}