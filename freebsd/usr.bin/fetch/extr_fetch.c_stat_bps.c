#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {double tv_usec; scalar_t__ tv_sec; } ;
struct xferstat {double rcvd; double lastrcvd; TYPE_1__ last2; TYPE_2__ last; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  stat_bytes (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
stat_bps(char *str, size_t strsz, struct xferstat *xs)
{
	char bytes[16];
	double delta, bps;

	delta = ((double)xs->last.tv_sec + (xs->last.tv_usec / 1.e6))
	    - ((double)xs->last2.tv_sec + (xs->last2.tv_usec / 1.e6));

	if (delta == 0.0) {
		snprintf(str, strsz, "?? Bps");
	} else {
		bps = (xs->rcvd - xs->lastrcvd) / delta;
		stat_bytes(bytes, sizeof bytes, (off_t)bps);
		snprintf(str, strsz, "%sps", bytes);
	}
}