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
typedef  char uint8_t ;
typedef  char u_char ;

/* Variables and functions */
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ isspace (char const) ; 
 scalar_t__ isupper (char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hex2bin(const char *str, uint8_t *buf, int buf_size)
{
	int i;
	u_char c;

	memset(buf, 0, buf_size);
	while (isspace(str[0]))
		str++;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	buf_size *= 2;
	for (i = 0; str[i] != 0 && i < buf_size; i++) {
		while (str[i] == '-')	/* Skip dashes in UUIDs. */
			str++;
		c = str[i];
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= 16)
			break;
		if ((i & 1) == 0)
			buf[i / 2] |= (c << 4);
		else
			buf[i / 2] |= c;
	}
	return ((i + 1) / 2);
}