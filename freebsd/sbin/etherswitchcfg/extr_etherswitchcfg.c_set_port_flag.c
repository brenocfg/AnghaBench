#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct cfg {int /*<<< orphan*/  fd; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  p ;
struct TYPE_4__ {int /*<<< orphan*/  es_flags; int /*<<< orphan*/  es_port; } ;
typedef  TYPE_1__ etherswitch_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERSWITCH_PORT_ADDTAG ; 
 int /*<<< orphan*/  ETHERSWITCH_PORT_DOUBLE_TAG ; 
 int /*<<< orphan*/  ETHERSWITCH_PORT_DROPTAGGED ; 
 int /*<<< orphan*/  ETHERSWITCH_PORT_DROPUNTAGGED ; 
 int /*<<< orphan*/  ETHERSWITCH_PORT_FIRSTLOCK ; 
 int /*<<< orphan*/  ETHERSWITCH_PORT_INGRESS ; 
 int /*<<< orphan*/  ETHERSWITCH_PORT_STRIPTAG ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  IOETHERSWITCHGETPORT ; 
 int /*<<< orphan*/  IOETHERSWITCHSETPORT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
set_port_flag(struct cfg *cfg, int argc, char *argv[])
{
	char *flag;
	int n;
	uint32_t f;
	etherswitch_port_t p;

	if (argc < 1)
		return (-1);

	n = 0;
	f = 0;
	flag = argv[0];
	if (strcmp(flag, "none") != 0) {
		if (*flag == '-') {
			n++;
			flag++;
		}
		if (strcasecmp(flag, "striptag") == 0)
			f = ETHERSWITCH_PORT_STRIPTAG;
		else if (strcasecmp(flag, "addtag") == 0)
			f = ETHERSWITCH_PORT_ADDTAG;
		else if (strcasecmp(flag, "firstlock") == 0)
			f = ETHERSWITCH_PORT_FIRSTLOCK;
		else if (strcasecmp(flag, "droptagged") == 0)
			f = ETHERSWITCH_PORT_DROPTAGGED;
		else if (strcasecmp(flag, "dropuntagged") == 0)
			f = ETHERSWITCH_PORT_DROPUNTAGGED;
		else if (strcasecmp(flag, "doubletag") == 0)
			f = ETHERSWITCH_PORT_DOUBLE_TAG;
		else if (strcasecmp(flag, "ingress") == 0)
			f = ETHERSWITCH_PORT_INGRESS;
	}
	bzero(&p, sizeof(p));
	p.es_port = cfg->unit;
	if (ioctl(cfg->fd, IOETHERSWITCHGETPORT, &p) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETPORT)");
	if (n)
		p.es_flags &= ~f;
	else
		p.es_flags |= f;
	if (ioctl(cfg->fd, IOETHERSWITCHSETPORT, &p) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHSETPORT)");
	return (0);
}