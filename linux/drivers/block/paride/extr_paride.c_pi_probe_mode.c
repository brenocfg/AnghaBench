#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mode; int port; int reserved; TYPE_1__* proto; } ;
struct TYPE_5__ {int epp_first; } ;
typedef  TYPE_2__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  pi_test_proto (TYPE_2__*,char*,int) ; 

__attribute__((used)) static int pi_probe_mode(PIA * pi, int max, char *scratch, int verbose)
{
	int best, range;

	if (pi->mode != -1) {
		if (pi->mode >= max)
			return 0;
		range = 3;
		if (pi->mode >= pi->proto->epp_first)
			range = 8;
		if ((range == 8) && (pi->port % 8))
			return 0;
		pi->reserved = range;
		return (!pi_test_proto(pi, scratch, verbose));
	}
	best = -1;
	for (pi->mode = 0; pi->mode < max; pi->mode++) {
		range = 3;
		if (pi->mode >= pi->proto->epp_first)
			range = 8;
		if ((range == 8) && (pi->port % 8))
			break;
		pi->reserved = range;
		if (!pi_test_proto(pi, scratch, verbose))
			best = pi->mode;
	}
	pi->mode = best;
	return (best > -1);
}