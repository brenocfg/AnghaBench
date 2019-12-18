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
typedef  int /*<<< orphan*/  u_char ;
typedef  int (* leapsec_reader ) (void*) ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 int stub1 (void*) ; 

__attribute__((used)) static char *
get_line(
	leapsec_reader func,
	void *         farg,
	char *         buff,
	size_t         size)
{
	int   ch;
	char *ptr;

	/* if we cannot even store the delimiter, declare failure */
	if (buff == NULL || size == 0)
		return NULL;

	ptr = buff;
	while (EOF != (ch = (*func)(farg)) && '\n' != ch)
		if (size > 1) {
			size--;
			*ptr++ = (char)ch;
		}
	/* discard trailing whitespace */
	while (ptr != buff && isspace((u_char)ptr[-1]))
		ptr--;
	*ptr = '\0';
	return (ptr == buff && ch == EOF) ? NULL : buff;
}