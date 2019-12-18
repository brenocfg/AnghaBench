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
typedef  int wchar_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  show_mb (char const*) ; 
 int /*<<< orphan*/  werr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
towide_dbcs(wchar_t *wc, const char *mb, unsigned n)
{
	wchar_t	c;

	c = *(const uint8_t *)mb;

	if ((c & 0x80) == 0) {
		/* 7-bit */
		*wc = c;
		return (1);
	}
	if (n < 2) {
		werr("incomplete character sequence (%s)", show_mb(mb));
		return (-1);
	}

	/* Store both bytes as a single 16-bit wide. */
	c <<= 8;
	c |= (uint8_t)(mb[1]);
	*wc = c;
	return (2);
}