#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32 ;
typedef  scalar_t__ u_int ;
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  tag ;
struct TYPE_3__ {int flags; char const* name; int last_ttl; int num_mcast; int received; int sent; int notsent; scalar_t__ starttime; scalar_t__ peercnt; int /*<<< orphan*/  ignore_packets; int /*<<< orphan*/  bcast; int /*<<< orphan*/  sin; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 scalar_t__ COUNTOF (scalar_t__*) ; 
 int IFSTATS_FIELDS ; 
 int INT_BCASTOPEN ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZERO (scalar_t__*) ; 
 int /*<<< orphan*/  ctl_puthex (char*,scalar_t__) ; 
 int /*<<< orphan*/  ctl_putint (char*,int) ; 
 int /*<<< orphan*/  ctl_putstr (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putuint (char*,scalar_t__) ; 
 int /*<<< orphan*/  ctl_putunqstr (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ current_time ; 
 int rand () ; 
 int /*<<< orphan*/  send_random_tag_value (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,scalar_t__) ; 
 char* sptoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
send_ifstats_entry(
	endpt *	la,
	u_int	ifnum
	)
{
	const char addr_fmtu[] =	"addr.%u";
	const char bcast_fmt[] =	"bcast.%u";
	const char en_fmt[] =		"en.%u";	/* enabled */
	const char name_fmt[] =		"name.%u";
	const char flags_fmt[] =	"flags.%u";
	const char tl_fmt[] =		"tl.%u";	/* ttl */
	const char mc_fmt[] =		"mc.%u";	/* mcast count */
	const char rx_fmt[] =		"rx.%u";
	const char tx_fmt[] =		"tx.%u";
	const char txerr_fmt[] =	"txerr.%u";
	const char pc_fmt[] =		"pc.%u";	/* peer count */
	const char up_fmt[] =		"up.%u";	/* uptime */
	char	tag[32];
	u_char	sent[IFSTATS_FIELDS]; /* 12 tag=value pairs */
	int	noisebits;
	u_int32 noise;
	u_int	which;
	u_int	remaining;
	const char *pch;

	remaining = COUNTOF(sent);
	ZERO(sent);
	noise = 0;
	noisebits = 0;
	while (remaining > 0) {
		if (noisebits < 4) {
			noise = rand() ^ (rand() << 16);
			noisebits = 31;
		}
		which = (noise & 0xf) % COUNTOF(sent);
		noise >>= 4;
		noisebits -= 4;

		while (sent[which])
			which = (which + 1) % COUNTOF(sent);

		switch (which) {

		case 0:
			snprintf(tag, sizeof(tag), addr_fmtu, ifnum);
			pch = sptoa(&la->sin);
			ctl_putunqstr(tag, pch, strlen(pch));
			break;

		case 1:
			snprintf(tag, sizeof(tag), bcast_fmt, ifnum);
			if (INT_BCASTOPEN & la->flags)
				pch = sptoa(&la->bcast);
			else
				pch = "";
			ctl_putunqstr(tag, pch, strlen(pch));
			break;

		case 2:
			snprintf(tag, sizeof(tag), en_fmt, ifnum);
			ctl_putint(tag, !la->ignore_packets);
			break;

		case 3:
			snprintf(tag, sizeof(tag), name_fmt, ifnum);
			ctl_putstr(tag, la->name, strlen(la->name));
			break;

		case 4:
			snprintf(tag, sizeof(tag), flags_fmt, ifnum);
			ctl_puthex(tag, (u_int)la->flags);
			break;

		case 5:
			snprintf(tag, sizeof(tag), tl_fmt, ifnum);
			ctl_putint(tag, la->last_ttl);
			break;

		case 6:
			snprintf(tag, sizeof(tag), mc_fmt, ifnum);
			ctl_putint(tag, la->num_mcast);
			break;

		case 7:
			snprintf(tag, sizeof(tag), rx_fmt, ifnum);
			ctl_putint(tag, la->received);
			break;

		case 8:
			snprintf(tag, sizeof(tag), tx_fmt, ifnum);
			ctl_putint(tag, la->sent);
			break;

		case 9:
			snprintf(tag, sizeof(tag), txerr_fmt, ifnum);
			ctl_putint(tag, la->notsent);
			break;

		case 10:
			snprintf(tag, sizeof(tag), pc_fmt, ifnum);
			ctl_putuint(tag, la->peercnt);
			break;

		case 11:
			snprintf(tag, sizeof(tag), up_fmt, ifnum);
			ctl_putuint(tag, current_time - la->starttime);
			break;
		}
		sent[which] = TRUE;
		remaining--;
	}
	send_random_tag_value((int)ifnum);
}