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
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  vn_mode; int /*<<< orphan*/  count; int /*<<< orphan*/  first; int /*<<< orphan*/  last; int /*<<< orphan*/  rmtadr; } ;
typedef  TYPE_1__ mon_entry ;

/* Variables and functions */
 scalar_t__ COUNTOF (scalar_t__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZERO (scalar_t__*) ; 
 char* addr_fmt ; 
 int /*<<< orphan*/  ctl_puthex (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putts (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_putuint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putunqstr (char*,char const*,int /*<<< orphan*/ ) ; 
 char* last_fmt ; 
 int rand () ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,int) ; 
 char* sptoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
send_mru_entry(
	mon_entry *	mon,
	int		count
	)
{
	const char first_fmt[] =	"first.%d";
	const char ct_fmt[] =		"ct.%d";
	const char mv_fmt[] =		"mv.%d";
	const char rs_fmt[] =		"rs.%d";
	char	tag[32];
	u_char	sent[6]; /* 6 tag=value pairs */
	u_int32 noise;
	u_int	which;
	u_int	remaining;
	const char * pch;

	remaining = COUNTOF(sent);
	ZERO(sent);
	noise = (u_int32)(rand() ^ (rand() << 16));
	while (remaining > 0) {
		which = (noise & 7) % COUNTOF(sent);
		noise >>= 3;
		while (sent[which])
			which = (which + 1) % COUNTOF(sent);

		switch (which) {

		case 0:
			snprintf(tag, sizeof(tag), addr_fmt, count);
			pch = sptoa(&mon->rmtadr);
			ctl_putunqstr(tag, pch, strlen(pch));
			break;

		case 1:
			snprintf(tag, sizeof(tag), last_fmt, count);
			ctl_putts(tag, &mon->last);
			break;

		case 2:
			snprintf(tag, sizeof(tag), first_fmt, count);
			ctl_putts(tag, &mon->first);
			break;

		case 3:
			snprintf(tag, sizeof(tag), ct_fmt, count);
			ctl_putint(tag, mon->count);
			break;

		case 4:
			snprintf(tag, sizeof(tag), mv_fmt, count);
			ctl_putuint(tag, mon->vn_mode);
			break;

		case 5:
			snprintf(tag, sizeof(tag), rs_fmt, count);
			ctl_puthex(tag, mon->flags);
			break;
		}
		sent[which] = TRUE;
		remaining--;
	}
}