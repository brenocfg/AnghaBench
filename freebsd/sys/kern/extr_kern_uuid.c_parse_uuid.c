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
typedef  int u_int ;
struct uuid {int time_low; int time_mid; int time_hi_and_version; int clock_seq_hi_and_reserved; int clock_seq_low; int* node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bzero (struct uuid*,int) ; 
 int sscanf (char const*,char*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*) ; 
 int strlen (char const*) ; 

int
parse_uuid(const char *str, struct uuid *uuid)
{
	u_int c[11];
	int n;

	/* An empty string represents a nil UUID. */
	if (*str == '\0') {
		bzero(uuid, sizeof(*uuid));
		return (0);
	}

	/* The UUID string representation has a fixed length. */
	if (strlen(str) != 36)
		return (EINVAL);

	/*
	 * We only work with "new" UUIDs. New UUIDs have the form:
	 *      01234567-89ab-cdef-0123-456789abcdef
	 * The so called "old" UUIDs, which we don't support, have the form:
	 *      0123456789ab.cd.ef.01.23.45.67.89.ab
	 */
	if (str[8] != '-')
		return (EINVAL);

	n = sscanf(str, "%8x-%4x-%4x-%2x%2x-%2x%2x%2x%2x%2x%2x", c + 0, c + 1,
	    c + 2, c + 3, c + 4, c + 5, c + 6, c + 7, c + 8, c + 9, c + 10);
	/* Make sure we have all conversions. */
	if (n != 11)
		return (EINVAL);

	/* Successful scan. Build the UUID. */
	uuid->time_low = c[0];
	uuid->time_mid = c[1];
	uuid->time_hi_and_version = c[2];
	uuid->clock_seq_hi_and_reserved = c[3];
	uuid->clock_seq_low = c[4];
	for (n = 0; n < 6; n++)
		uuid->node[n] = c[n + 5];

	/* Check semantics... */
	return (((c[3] & 0x80) != 0x00 &&		/* variant 0? */
	    (c[3] & 0xc0) != 0x80 &&			/* variant 1? */
	    (c[3] & 0xe0) != 0xc0) ? EINVAL : 0);	/* variant 2? */
}