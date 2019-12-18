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
struct ofwo_extabent {char* ex_prop; int /*<<< orphan*/  (* ex_handler ) (struct ofwo_extabent const*,int,void*,int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  prop ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OFWO_MAXPROP ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  ofw_close (int) ; 
 int ofw_firstprop (int,int /*<<< orphan*/ ,char*,int) ; 
 int ofw_getprop_alloc (int,int /*<<< orphan*/ ,char*,void**,int*,int) ; 
 int ofw_nextprop (int,int /*<<< orphan*/ ,char*,char*,int) ; 
 int ofw_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_optnode (int) ; 
 struct ofwo_extabent* ofwo_extab ; 
 int /*<<< orphan*/  ofwo_printprop (char*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct ofwo_extabent const*,int,void*,int,int /*<<< orphan*/ *) ; 

void
ofwo_dump(void)
{
	void *pbuf;
	int fd, len, nlen, pblen;
	phandle_t optnode;
	char prop[OFWO_MAXPROP + 1];
	const struct ofwo_extabent *ex;

	pblen = 0;
	pbuf = NULL;
	fd = ofw_open(O_RDONLY);
	optnode = ofw_optnode(fd);
	for (nlen = ofw_firstprop(fd, optnode, prop, sizeof(prop)); nlen != 0;
	    nlen = ofw_nextprop(fd, optnode, prop, prop, sizeof(prop))) {
		len = ofw_getprop_alloc(fd, optnode, prop, &pbuf, &pblen, 1);
		if (len < 0)
			continue;
		if (strcmp(prop, "name") == 0)
			continue;
		for (ex = ofwo_extab; ex->ex_prop != NULL; ++ex)
			if (strcmp(ex->ex_prop, prop) == 0)
				break;
		if (ex->ex_prop != NULL)
			(*ex->ex_handler)(ex, fd, pbuf, len, NULL);
		else
			ofwo_printprop(prop, (char *)pbuf, len);
	}
	if (pbuf != NULL)
		free(pbuf);
	ofw_close(fd);
}