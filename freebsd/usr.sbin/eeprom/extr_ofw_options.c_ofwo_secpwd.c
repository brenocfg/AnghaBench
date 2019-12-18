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
struct ofwo_extabent {int /*<<< orphan*/  ex_prop; } ;

/* Variables and functions */
 int EX_CONFIG ; 
 int EX_OK ; 
 int /*<<< orphan*/  free (void*) ; 
 int ofw_getprop_alloc (int,int /*<<< orphan*/ ,char*,void**,int*,int) ; 
 int /*<<< orphan*/  ofw_optnode (int) ; 
 int /*<<< orphan*/  ofwo_printprop (int /*<<< orphan*/ ,char const*,int) ; 
 int ofwo_setpass (int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
ofwo_secpwd(const struct ofwo_extabent *exent, int fd, const void *buf,
    int buflen, const char *val)
{
	void *pbuf;
	int len, pblen, rv;

	pblen = 0;
	rv = EX_OK;
	pbuf = NULL;
	if (val) {
		len = ofw_getprop_alloc(fd, ofw_optnode(fd), "security-mode",
		    &pbuf, &pblen, 1);
		if (len <= 0 || strncmp("none", (char *)pbuf, len) == 0) {
			rv = EX_CONFIG;
			warnx("no security mode set.");
		} else if (strncmp("command", (char *)pbuf, len) == 0 ||
		    strncmp("full", (char *)pbuf, len) == 0) {
			rv = ofwo_setpass(fd);
		} else {
			rv = EX_CONFIG;
			warnx("invalid security mode.");
		}
	} else
		ofwo_printprop(exent->ex_prop, (const char *)buf, buflen);
	if (pbuf != NULL)
		free(pbuf);
	return (rv);
}