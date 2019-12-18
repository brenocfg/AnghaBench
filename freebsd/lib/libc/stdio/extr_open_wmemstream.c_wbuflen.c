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
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 size_t mbrlen (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
wbuflen(const mbstate_t *state, const char *buf, int len)
{
	mbstate_t lenstate;
	size_t charlen, count;

	count = 0;
	lenstate = *state;
	while (len > 0) {
		charlen = mbrlen(buf, len, &lenstate);
		if (charlen == (size_t)-1)
			return (-1);
		if (charlen == (size_t)-2)
			break;
		if (charlen == 0)
			/* XXX: Not sure how else to handle this. */
			charlen = 1;
		len -= charlen;
		buf += charlen;
		count++;
	}
	return (count);
}