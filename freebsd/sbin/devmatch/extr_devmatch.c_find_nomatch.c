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
struct exact_info {char* loc; char* bus; TYPE_1__* dev; } ;
struct TYPE_2__ {int dd_flags; } ;

/* Variables and functions */
 int DF_ATTACHED_ONCE ; 
 int /*<<< orphan*/  devinfo_foreach_device_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_exact_dev ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  search_hints (char*,char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
find_nomatch(char *nomatch)
{
	char *bus, *pnpinfo, *tmp, *busnameunit;
	struct exact_info info;

	/*
	 * Find our bus name. It will include the unit number. We have to search
	 * backwards to avoid false positive for any PNP string that has ' on '
	 * in them, which would come earlier in the string. Like if there were
	 * an 'Old Bard' ethernet card made by 'Stratford on Avon Hardware' or
	 * something silly like that.
	 */
	tmp = nomatch + strlen(nomatch) - 4;
	while (tmp > nomatch && strncmp(tmp, " on ", 4) != 0)
		tmp--;
	if (tmp == nomatch)
		errx(1, "No bus found in nomatch string: '%s'", nomatch);
	bus = tmp + 4;
	*tmp = '\0';
	busnameunit = strdup(bus);
	if (busnameunit == NULL)
		errx(1, "Can't allocate memory for strings");
	tmp = bus + strlen(bus) - 1;
	while (tmp > bus && isdigit(*tmp))
		tmp--;
	*++tmp = '\0';

	/*
	 * Note: the NOMATCH events place both the bus location as well as the
	 * pnp info after the 'at' and we don't know where one stops and the
	 * other begins, so we pass the whole thing to our search routine.
	 */
	if (*nomatch == '?')
		nomatch++;
	if (strncmp(nomatch, " at ", 4) != 0)
		errx(1, "Malformed NOMATCH string: '%s'", nomatch);
	pnpinfo = nomatch + 4;

	/*
	 * See if we can find the devinfo_dev for this device. If we
	 * can, and it's been attached before, we should filter it out
	 * so that a kldunload foo doesn't cause an immediate reload.
	 */
	info.loc = pnpinfo;
	info.bus = busnameunit;
	info.dev = NULL;
	devinfo_foreach_device_child(root, find_exact_dev, (void *)&info);
	if (info.dev != NULL && info.dev->dd_flags & DF_ATTACHED_ONCE)
		exit(0);
	search_hints(bus, "", pnpinfo);

	exit(0);
}