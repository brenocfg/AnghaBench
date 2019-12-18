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
struct TYPE_4__ {int es_nleds; int* es_led; int /*<<< orphan*/  es_port; } ;
typedef  TYPE_1__ etherswitch_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  IOETHERSWITCHGETPORT ; 
 int /*<<< orphan*/  IOETHERSWITCHSETPORT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ ** ledstyles ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_port_led(struct cfg *cfg, int argc, char *argv[])
{
	etherswitch_port_t p;
	int led;
	int i;

	if (argc < 3)
		return (-1);

	bzero(&p, sizeof(p));
	p.es_port = cfg->unit;
	if (ioctl(cfg->fd, IOETHERSWITCHGETPORT, &p) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETPORT)");

	led = strtol(argv[1], NULL, 0);
	if (led < 1 || led > p.es_nleds)
		errx(EX_USAGE, "invalid led number %s; must be between 1 and %d",
			argv[1], p.es_nleds);

	led--;

	for (i=0; ledstyles[i] != NULL; i++) {
		if (strcmp(argv[2], ledstyles[i]) == 0) {
			p.es_led[led] = i;
			break;
		}
	} 
	if (ledstyles[i] == NULL)
		errx(EX_USAGE, "invalid led style \"%s\"", argv[2]);

	if (ioctl(cfg->fd, IOETHERSWITCHSETPORT, &p) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHSETPORT)");

	return (0);
}