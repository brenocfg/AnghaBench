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
struct archive_read {int dummy; } ;

/* Variables and functions */
 char* __archive_read_ahead (struct archive_read*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
archive_read_format_zip_streamable_bid(struct archive_read *a, int best_bid)
{
	const char *p;

	(void)best_bid; /* UNUSED */

	if ((p = __archive_read_ahead(a, 4, NULL)) == NULL)
		return (-1);

	/*
	 * Bid of 29 here comes from:
	 *  + 16 bits for "PK",
	 *  + next 16-bit field has 6 options so contributes
	 *    about 16 - log_2(6) ~= 16 - 2.6 ~= 13 bits
	 *
	 * So we've effectively verified ~29 total bits of check data.
	 */
	if (p[0] == 'P' && p[1] == 'K') {
		if ((p[2] == '\001' && p[3] == '\002')
		    || (p[2] == '\003' && p[3] == '\004')
		    || (p[2] == '\005' && p[3] == '\006')
		    || (p[2] == '\006' && p[3] == '\006')
		    || (p[2] == '\007' && p[3] == '\010')
		    || (p[2] == '0' && p[3] == '0'))
			return (29);
	}

	/* TODO: It's worth looking ahead a little bit for a valid
	 * PK signature.  In particular, that would make it possible
	 * to read some UUEncoded SFX files or SFX files coming from
	 * a network socket. */

	return (0);
}