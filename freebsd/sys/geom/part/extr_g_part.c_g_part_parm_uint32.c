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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int ;
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOATTR ; 
 scalar_t__ const INT_MAX ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,int,char const*,unsigned int) ; 
 scalar_t__* gctl_get_param (struct gctl_req*,char const*,int*) ; 

__attribute__((used)) static int
g_part_parm_uint32(struct gctl_req *req, const char *name, u_int *v)
{
	const uint32_t *p;
	int size;

	p = gctl_get_param(req, name, &size);
	if (p == NULL)
		return (ENOATTR);
	if (size != sizeof(*p) || *p > INT_MAX) {
		gctl_error(req, "%d %s '%u'", EINVAL, name, (unsigned int)*p);
		return (EINVAL);
	}
	*v = (u_int)*p;
	return (0);
}