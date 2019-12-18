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
struct bt_devaddr_match_arg {char* devname; int /*<<< orphan*/  const* bdaddr; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  HCI_DEVNAME_SIZE ; 
 int /*<<< orphan*/  bt_devaddr_match ; 
 scalar_t__ bt_devenum (int /*<<< orphan*/ *,struct bt_devaddr_match_arg*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct bt_devaddr_match_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 

int
bt_devname(char *devname, bdaddr_t const *addr)
{
	struct bt_devaddr_match_arg	arg;

	memset(&arg, 0, sizeof(arg));
	arg.bdaddr = addr;

	if (bt_devenum(&bt_devaddr_match, &arg) < 0)
		return (0);
	
	if (arg.devname[0] == '\0') {
		errno = ENXIO;
		return (0);
	}

	if (devname != NULL)
		strlcpy(devname, arg.devname, HCI_DEVNAME_SIZE);

	return (1);
}