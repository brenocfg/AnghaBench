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
struct pf_osfp_ioctl {int fp_getnum; } ;
typedef  int /*<<< orphan*/  io ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCOSFPGET ; 
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  classes ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  import_fingerprint (struct pf_osfp_ioctl*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pf_osfp_ioctl*) ; 
 int /*<<< orphan*/  memset (struct pf_osfp_ioctl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfctl_flush_my_fingerprints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
pfctl_load_fingerprints(int dev, int opts)
{
	struct pf_osfp_ioctl io;
	int i;

	pfctl_flush_my_fingerprints(&classes);

	for (i = 0; i >= 0; i++) {
		memset(&io, 0, sizeof(io));
		io.fp_getnum = i;
		if (ioctl(dev, DIOCOSFPGET, &io)) {
			if (errno == EBUSY)
				break;
			warn("DIOCOSFPGET");
			return (1);
		}
		import_fingerprint(&io);
	}
	return (0);
}