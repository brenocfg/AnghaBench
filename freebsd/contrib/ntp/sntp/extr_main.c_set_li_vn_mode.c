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
struct pkt {char li_vn_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 

void
set_li_vn_mode (
	struct pkt *spkt,
	char leap,
	char version,
	char mode
	)
{
	if (leap > 3) {
		msyslog(LOG_DEBUG, "set_li_vn_mode: leap > 3, using max. 3");
		leap = 3;
	}

	if ((unsigned char)version > 7) {
		msyslog(LOG_DEBUG, "set_li_vn_mode: version < 0 or > 7, using 4");
		version = 4;
	}

	if (mode > 7) {
		msyslog(LOG_DEBUG, "set_li_vn_mode: mode > 7, using client mode 3");
		mode = 3;
	}

	spkt->li_vn_mode  = leap << 6;
	spkt->li_vn_mode |= version << 3;
	spkt->li_vn_mode |= mode;
}