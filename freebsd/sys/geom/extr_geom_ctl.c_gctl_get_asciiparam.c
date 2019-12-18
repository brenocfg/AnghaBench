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
typedef  size_t u_int ;
struct gctl_req_arg {int flag; char* kvalue; int len; int /*<<< orphan*/  name; } ;
struct gctl_req {size_t narg; struct gctl_req_arg* arg; } ;

/* Variables and functions */
 int GCTL_PARAM_RD ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

char const *
gctl_get_asciiparam(struct gctl_req *req, const char *param)
{
	u_int i;
	char const *p;
	struct gctl_req_arg *ap;

	for (i = 0; i < req->narg; i++) {
		ap = &req->arg[i];
		if (strcmp(param, ap->name))
			continue;
		if (!(ap->flag & GCTL_PARAM_RD))
			continue;
		p = ap->kvalue;
		if (ap->len < 1) {
			gctl_error(req, "No length argument (%s)", param);
			return (NULL);
		}
		if (p[ap->len - 1] != '\0') {
			gctl_error(req, "Unterminated argument (%s)", param);
			return (NULL);
		}
		return (p);
	}
	return (NULL);
}