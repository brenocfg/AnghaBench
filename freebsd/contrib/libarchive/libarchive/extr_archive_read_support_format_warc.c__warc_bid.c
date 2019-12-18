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
typedef  int ssize_t ;

/* Variables and functions */
 char* __archive_read_ahead (struct archive_read*,unsigned int,int*) ; 
 unsigned int _warc_rdver (char const*,int) ; 

__attribute__((used)) static int
_warc_bid(struct archive_read *a, int best_bid)
{
	const char *hdr;
	ssize_t nrd;
	unsigned int ver;

	(void)best_bid; /* UNUSED */

	/* check first line of file, it should be a record already */
	if ((hdr = __archive_read_ahead(a, 12U, &nrd)) == NULL) {
		/* no idea what to do */
		return -1;
	} else if (nrd < 12) {
		/* nah, not for us, our magic cookie is at least 12 bytes */
		return -1;
	}

	/* otherwise snarf the record's version number */
	ver = _warc_rdver(hdr, nrd);
	if (ver < 1200U || ver > 10000U) {
		/* we only support WARC 0.12 to 1.0 */
		return -1;
	}

	/* otherwise be confident */
	return (64);
}