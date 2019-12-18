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
struct ofwo_extabent {char const* ex_prop; int (* ex_handler ) (struct ofwo_extabent const*,int,void*,int,char const*) ;} ;

/* Variables and functions */
 int EX_OK ; 
 int EX_UNAVAILABLE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  ofw_close (int) ; 
 int ofw_getprop_alloc (int,int /*<<< orphan*/ ,char const*,void**,int*,int) ; 
 int ofw_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_optnode (int) ; 
 struct ofwo_extabent* ofwo_extab ; 
 int /*<<< orphan*/  ofwo_printprop (char const*,char*,int) ; 
 int ofwo_setstr (int,void*,int,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int stub1 (struct ofwo_extabent const*,int,void*,int,char const*) ; 

int
ofwo_action(const char *prop, const char *val)
{
	void *pbuf;
	int fd, len, pblen, rv;
	const struct ofwo_extabent *ex;

	pblen = 0;
	rv = EX_OK;
	pbuf = NULL;
	if (strcmp(prop, "name") == 0)
		return (EX_UNAVAILABLE);
	if (val)
		fd = ofw_open(O_RDWR);
	else
		fd = ofw_open(O_RDONLY);
	len = ofw_getprop_alloc(fd, ofw_optnode(fd), prop, &pbuf, &pblen, 1);
	if (len < 0) {
		rv = EX_UNAVAILABLE;
		goto out;
	}
	for (ex = ofwo_extab; ex->ex_prop != NULL; ++ex)
		if (strcmp(ex->ex_prop, prop) == 0)
			break;
	if (ex->ex_prop != NULL)
		rv = (*ex->ex_handler)(ex, fd, pbuf, len, val);
	else if (val)
		rv = ofwo_setstr(fd, pbuf, len, prop, val);
	else
		ofwo_printprop(prop, (char *)pbuf, len);
out:
	if (pbuf != NULL)
		free(pbuf);
	ofw_close(fd);
	return (rv);
}