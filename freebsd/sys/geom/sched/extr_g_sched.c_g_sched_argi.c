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
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,int) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static const char *
g_sched_argi(struct gctl_req *req, int i)
{
	static const char *dev_prefix = "/dev/";
	const char *name;
	char param[16];
	int l = strlen(dev_prefix);

	snprintf(param, sizeof(param), "arg%d", i);
	name = gctl_get_asciiparam(req, param);
	if (name == NULL)
		gctl_error(req, "No 'arg%d' argument", i);
	else if (strncmp(name, dev_prefix, l) == 0)
		name += l;
	return (name);
}