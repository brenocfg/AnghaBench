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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_fdt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ isxdigit (char const) ; 
 int strlen (char const*) ; 
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
_fdt_strtovect(const char *str, void *cellbuf, int lim, unsigned char cellsize,
    uint8_t base)
{
	const char *buf = str;
	const char *end = str + strlen(str) - 2;
	uint32_t *u32buf = NULL;
	uint8_t *u8buf = NULL;
	int cnt = 0;

	if (cellsize == sizeof(uint32_t))
		u32buf = (uint32_t *)cellbuf;
	else
		u8buf = (uint8_t *)cellbuf;

	if (lim == 0)
		return (0);

	while (buf < end) {

		/* Skip white whitespace(s)/separators */
		while (!isxdigit(*buf) && buf < end)
			buf++;

		if (u32buf != NULL)
			u32buf[cnt] =
			    cpu_to_fdt32((uint32_t)strtol(buf, NULL, base));

		else
			u8buf[cnt] = (uint8_t)strtol(buf, NULL, base);

		if (cnt + 1 <= lim - 1)
			cnt++;
		else
			break;
		buf++;
		/* Find another number */
		while ((isxdigit(*buf) || *buf == 'x') && buf < end)
			buf++;
	}
	return (cnt);
}