#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32 ;
typedef  scalar_t__ u_int ;
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  tag ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_4__ {int /*<<< orphan*/  rflags; int /*<<< orphan*/  mflags; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ restrict_u ;

/* Variables and functions */
 scalar_t__ COUNTOF (scalar_t__*) ; 
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int RESLIST_FIELDS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZERO (scalar_t__*) ; 
 int /*<<< orphan*/  ctl_putuint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putunqstr (char*,char const*,int /*<<< orphan*/ ) ; 
 int rand () ; 
 char* res_access_flags (int /*<<< orphan*/ ) ; 
 char* res_match_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_random_tag_value (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,char const*,...) ; 
 int /*<<< orphan*/  sockaddrs_from_restrict_u (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 char* stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
send_restrict_entry(
	restrict_u *	pres,
	int		ipv6,
	u_int		idx
	)
{
	const char addr_fmtu[] =	"addr.%u";
	const char mask_fmtu[] =	"mask.%u";
	const char hits_fmt[] =		"hits.%u";
	const char flags_fmt[] =	"flags.%u";
	char		tag[32];
	u_char		sent[RESLIST_FIELDS]; /* 4 tag=value pairs */
	int		noisebits;
	u_int32		noise;
	u_int		which;
	u_int		remaining;
	sockaddr_u	addr;
	sockaddr_u	mask;
	const char *	pch;
	char *		buf;
	const char *	match_str;
	const char *	access_str;

	sockaddrs_from_restrict_u(&addr, &mask, pres, ipv6);
	remaining = COUNTOF(sent);
	ZERO(sent);
	noise = 0;
	noisebits = 0;
	while (remaining > 0) {
		if (noisebits < 2) {
			noise = rand() ^ (rand() << 16);
			noisebits = 31;
		}
		which = (noise & 0x3) % COUNTOF(sent);
		noise >>= 2;
		noisebits -= 2;

		while (sent[which])
			which = (which + 1) % COUNTOF(sent);

		/* XXX: Numbers?  Really? */
		switch (which) {

		case 0:
			snprintf(tag, sizeof(tag), addr_fmtu, idx);
			pch = stoa(&addr);
			ctl_putunqstr(tag, pch, strlen(pch));
			break;

		case 1:
			snprintf(tag, sizeof(tag), mask_fmtu, idx);
			pch = stoa(&mask);
			ctl_putunqstr(tag, pch, strlen(pch));
			break;

		case 2:
			snprintf(tag, sizeof(tag), hits_fmt, idx);
			ctl_putuint(tag, pres->count);
			break;

		case 3:
			snprintf(tag, sizeof(tag), flags_fmt, idx);
			match_str = res_match_flags(pres->mflags);
			access_str = res_access_flags(pres->rflags);
			if ('\0' == match_str[0]) {
				pch = access_str;
			} else {
				LIB_GETBUF(buf);
				snprintf(buf, LIB_BUFLENGTH, "%s %s",
					 match_str, access_str);
				pch = buf;
			}
			ctl_putunqstr(tag, pch, strlen(pch));
			break;
		}
		sent[which] = TRUE;
		remaining--;
	}
	send_random_tag_value((int)idx);
}