#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty {int dummy; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  output ;
struct TYPE_2__ {scalar_t__ cn_pri; char* cn_name; } ;

/* Variables and functions */
 scalar_t__ CN_DEAD ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,char*,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ ofw_consdev ; 
 int /*<<< orphan*/  ofw_timer ; 
 int /*<<< orphan*/  ofw_ttydevsw ; 
 scalar_t__ strlen (char*) ; 
 struct tty* tty_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_getlock (struct tty*) ; 
 int /*<<< orphan*/  tty_makealias (struct tty*,char*,char*) ; 
 int /*<<< orphan*/  tty_makedev (struct tty*,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void
cn_drvinit(void *unused)
{
	phandle_t options;
	char output[32];
	struct tty *tp;

	if (ofw_consdev.cn_pri != CN_DEAD &&
	    ofw_consdev.cn_name[0] != '\0') {
		tp = tty_alloc(&ofw_ttydevsw, NULL);
		tty_makedev(tp, NULL, "%s", "ofwcons");

		/*
		 * XXX: This is a hack and it may result in two /dev/ttya
		 * XXX: devices on platforms where the sab driver works.
		 */
		if ((options = OF_finddevice("/options")) == -1 ||
		    OF_getprop(options, "output-device", output,
		    sizeof(output)) == -1)
			return;
		if (strlen(output) > 0)
			tty_makealias(tp, "%s", output);
		callout_init_mtx(&ofw_timer, tty_getlock(tp), 0);
	}
}