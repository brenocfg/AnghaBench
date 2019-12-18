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
struct pfioc_altq {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETALTQS ; 
 scalar_t__ ENODEV ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  PFIOC_ALTQ_VERSION ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_altq*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
altq_is_enabled(int pfdev)
{
	struct pfioc_altq pa;

	errno = 0;
	pa.version = PFIOC_ALTQ_VERSION;
	if (ioctl(pfdev, DIOCGETALTQS, &pa)) {
		if (errno == ENODEV) {
			syslog(LOG_INFO, "No ALTQ support in kernel\n"
			    "ALTQ related functions disabled\n");
			return (0);
		} else
			syslog(LOG_ERR, "DIOCGETALTQS returned an error: %s",
			    strerror(errno));
			return (-1);
	}
	return (1);
}