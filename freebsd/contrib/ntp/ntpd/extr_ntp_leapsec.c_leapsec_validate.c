#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hv; } ;
typedef  TYPE_1__ sha1_digest ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  leapsec_reader ;
typedef  int /*<<< orphan*/  isc_sha1_t ;

/* Variables and functions */
 int LSVALID_BADFORMAT ; 
 int LSVALID_BADHASH ; 
 int LSVALID_GOODHASH ; 
 int LSVALID_NOHASH ; 
 int /*<<< orphan*/  do_hash_data (int /*<<< orphan*/ *,char*) ; 
 int do_leap_hash (TYPE_1__*,char*) ; 
 scalar_t__ get_line (int /*<<< orphan*/ ,void*,char*,int) ; 
 int /*<<< orphan*/  isc_sha1_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_sha1_invalidate (int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ memcmp (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int
leapsec_validate(
	leapsec_reader func,
	void *         farg)
{
	isc_sha1_t     mdctx;
	sha1_digest    rdig, ldig; /* remote / local digests */
	char           line[50];
	int            hlseen = -1;

	isc_sha1_init(&mdctx);
	while (get_line(func, farg, line, sizeof(line))) {
		if (!strncmp(line, "#h", 2))
			hlseen = do_leap_hash(&rdig, line+2);
		else if (!strncmp(line, "#@", 2))
			do_hash_data(&mdctx, line+2);
		else if (!strncmp(line, "#$", 2))
			do_hash_data(&mdctx, line+2);
		else if (isdigit((unsigned char)line[0]))
			do_hash_data(&mdctx, line);
	}
	isc_sha1_final(&mdctx, ldig.hv);
	isc_sha1_invalidate(&mdctx);

	if (0 > hlseen)
		return LSVALID_NOHASH;
	if (0 == hlseen)
		return LSVALID_BADFORMAT;
	if (0 != memcmp(&rdig, &ldig, sizeof(sha1_digest)))
		return LSVALID_BADHASH;
	return LSVALID_GOODHASH;
}