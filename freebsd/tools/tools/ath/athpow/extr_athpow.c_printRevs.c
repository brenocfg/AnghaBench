#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ah_devid; int ah_subvendorid; int ah_macVersion; int ah_macRev; int ah_phyRev; int ah_analog5GhzRev; int ah_analog2GhzRev; } ;
typedef  TYPE_1__ HAL_REVS ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IS_2413 (TYPE_1__ const*) ; 
 scalar_t__ IS_5112 (TYPE_1__ const*) ; 
 scalar_t__ IS_5413 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,...) ; 

__attribute__((used)) static void
printRevs(FILE *fd, const HAL_REVS *revs)
{
	const char *rfbackend;

	fprintf(fd, "PCI device id 0x%x subvendor id 0x%x\n",
		revs->ah_devid, revs->ah_subvendorid);
	fprintf(fd, "mac %d.%d phy %d.%d"
		, revs->ah_macVersion, revs->ah_macRev
		, revs->ah_phyRev >> 4, revs->ah_phyRev & 0xf
	);
	rfbackend = IS_5413(revs) ? "5413" :
		    IS_2413(revs) ? "2413" :
		    IS_5112(revs) ? "5112" :
				    "5111";
	if (revs->ah_analog5GhzRev && revs->ah_analog2GhzRev)
		fprintf(fd, " 5ghz radio %d.%d 2ghz radio %d.%d (%s)\n"
			, revs->ah_analog5GhzRev >> 4
			, revs->ah_analog5GhzRev & 0xf
			, revs->ah_analog2GhzRev >> 4
			, revs->ah_analog2GhzRev & 0xf
			, rfbackend
		);
	else
		fprintf(fd, " radio %d.%d (%s)\n"
			, revs->ah_analog5GhzRev >> 4
			, revs->ah_analog5GhzRev & 0xf
			, rfbackend
		);
}