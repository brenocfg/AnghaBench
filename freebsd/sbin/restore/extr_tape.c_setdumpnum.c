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
struct mtop {int mt_count; int /*<<< orphan*/  mt_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTFSF ; 
 int /*<<< orphan*/  MTIOCTOP ; 
 int /*<<< orphan*/  done (int) ; 
 int dumpnum ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ host ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mt ; 
 int /*<<< orphan*/  pipecmdin ; 
 scalar_t__ pipein ; 
 int /*<<< orphan*/  rmtioctl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int volno ; 

__attribute__((used)) static void
setdumpnum(void)
{
	struct mtop tcom;

	if (dumpnum == 1 || volno != 1)
		return;
	if (pipein) {
		fprintf(stderr, "Cannot have multiple dumps on pipe input\n");
		done(1);
	}
	tcom.mt_op = MTFSF;
	tcom.mt_count = dumpnum - 1;
#ifdef RRESTORE
	if (host)
		rmtioctl(MTFSF, dumpnum - 1);
	else
#endif
		if (!pipecmdin && ioctl(mt, MTIOCTOP, (char *)&tcom) < 0)
			fprintf(stderr, "ioctl MTFSF: %s\n", strerror(errno));
}