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
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,char const*) ; 
 void* gctl_get_param (struct gctl_req*,char const*,int*) ; 

void *
gctl_get_paraml_opt(struct gctl_req *req, const char *param, int len)
{
	int i;
	void *p;

	p = gctl_get_param(req, param, &i);
	if (i != len) {
		p = NULL;
		gctl_error(req, "Wrong length %s argument", param);
	}
	return (p);
}