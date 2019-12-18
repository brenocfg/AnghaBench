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
typedef  int /*<<< orphan*/  u_int32 ;
typedef  int /*<<< orphan*/  refid ;

/* Variables and functions */
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 char const* numtoa (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

const char *
refid_str(
	u_int32	refid,
	int	stratum
	)
{
	char *	text;
	size_t	tlen;

	if (stratum > 1)
		return numtoa(refid);

	LIB_GETBUF(text);
	text[0] = '.';
	memcpy(&text[1], &refid, sizeof(refid));
	text[1 + sizeof(refid)] = '\0';
	tlen = strlen(text);
	text[tlen] = '.';
	text[tlen + 1] = '\0';

	return text;
}