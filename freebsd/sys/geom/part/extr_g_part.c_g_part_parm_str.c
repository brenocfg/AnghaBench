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
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOATTR ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,int,char const*,char const*) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
g_part_parm_str(struct gctl_req *req, const char *name, const char **v)
{
	const char *p;

	p = gctl_get_asciiparam(req, name);
	if (p == NULL)
		return (ENOATTR);
	/* An empty label is always valid. */
	if (strcmp(name, "label") != 0 && p[0] == '\0') {
		gctl_error(req, "%d %s '%s'", EINVAL, name, p);
		return (EINVAL);
	}
	*v = p;
	return (0);
}