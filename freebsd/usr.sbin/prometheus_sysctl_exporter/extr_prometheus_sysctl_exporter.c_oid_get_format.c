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
struct oidformat {int dummy; } ;
struct oid {int len; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  lookup ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_MAXNAME ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sysctl (int*,int,struct oidformat*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
oid_get_format(const struct oid *o, struct oidformat *of)
{
	int lookup[CTL_MAXNAME + 2];
	size_t oflen;

	lookup[0] = 0;
	lookup[1] = 4;
	memcpy(lookup + 2, o->id, o->len * sizeof(lookup[0]));
	oflen = sizeof(*of);
	if (sysctl(lookup, 2 + o->len, of, &oflen, 0, 0) != 0) {
		if (errno == ENOENT)
			return (false);
		err(1, "sysctl(oidfmt)");
	}
	return (true);
}