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
struct cfg {int /*<<< orphan*/  fd; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  p ;
struct TYPE_4__ {int es_pvid; int /*<<< orphan*/  es_port; } ;
typedef  TYPE_1__ etherswitch_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int IEEE802DOT1Q_VID_MAX ; 
 int /*<<< orphan*/  IOETHERSWITCHGETPORT ; 
 int /*<<< orphan*/  IOETHERSWITCHSETPORT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_port_vid(struct cfg *cfg, int argc, char *argv[])
{
	int v;
	etherswitch_port_t p;

	if (argc < 2)
		return (-1);

	v = strtol(argv[1], NULL, 0);
	if (v < 0 || v > IEEE802DOT1Q_VID_MAX)
		errx(EX_USAGE, "pvid must be between 0 and %d",
		    IEEE802DOT1Q_VID_MAX);
	bzero(&p, sizeof(p));
	p.es_port = cfg->unit;
	if (ioctl(cfg->fd, IOETHERSWITCHGETPORT, &p) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETPORT)");
	p.es_pvid = v;
	if (ioctl(cfg->fd, IOETHERSWITCHSETPORT, &p) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHSETPORT)");
	return (0);
}