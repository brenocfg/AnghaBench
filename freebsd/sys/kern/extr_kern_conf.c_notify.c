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
struct cdev {char const* si_name; } ;
typedef  int /*<<< orphan*/  prefix ;

/* Variables and functions */
 int MAKEDEV_NOWAIT ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  devctl_notify_f (char*,char*,char const*,char*,int) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
notify(struct cdev *dev, const char *ev, int flags)
{
	static const char prefix[] = "cdev=";
	char *data;
	int namelen, mflags;

	if (cold)
		return;
	mflags = (flags & MAKEDEV_NOWAIT) ? M_NOWAIT : M_WAITOK;
	namelen = strlen(dev->si_name);
	data = malloc(namelen + sizeof(prefix), M_TEMP, mflags);
	if (data == NULL)
		return;
	memcpy(data, prefix, sizeof(prefix) - 1);
	memcpy(data + sizeof(prefix) - 1, dev->si_name, namelen + 1);
	devctl_notify_f("DEVFS", "CDEV", ev, data, mflags);
	free(data, M_TEMP);
}