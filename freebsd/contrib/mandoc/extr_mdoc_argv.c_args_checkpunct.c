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
typedef  enum mdelim { ____Placeholder_mdelim } mdelim ;

/* Variables and functions */
 int DELIMSZ ; 
 scalar_t__ DELIM_CLOSE ; 
 int DELIM_NONE ; 
 int DELIM_OPEN ; 
 scalar_t__ mdoc_isdelim (char*) ; 

__attribute__((used)) static int
args_checkpunct(const char *buf, int i)
{
	int		 j;
	char		 dbuf[DELIMSZ];
	enum mdelim	 d;

	/* First token must be a close-delimiter. */

	for (j = 0; buf[i] && ' ' != buf[i] && j < DELIMSZ; j++, i++)
		dbuf[j] = buf[i];

	if (DELIMSZ == j)
		return 0;

	dbuf[j] = '\0';
	if (DELIM_CLOSE != mdoc_isdelim(dbuf))
		return 0;

	while (' ' == buf[i])
		i++;

	/* Remaining must NOT be open/none. */

	while (buf[i]) {
		j = 0;
		while (buf[i] && ' ' != buf[i] && j < DELIMSZ)
			dbuf[j++] = buf[i++];

		if (DELIMSZ == j)
			return 0;

		dbuf[j] = '\0';
		d = mdoc_isdelim(dbuf);
		if (DELIM_NONE == d || DELIM_OPEN == d)
			return 0;

		while (' ' == buf[i])
			i++;
	}

	return '\0' == buf[i];
}