#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rrset_ns ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ rr_ns ;

/* Variables and functions */
 TYPE_1__* HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int ns_samename (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static rr_ns *
find_ns(rrset_ns *nsrrsp, const char *dname) {
	rr_ns *nsrr;

	for (nsrr = HEAD(*nsrrsp); nsrr != NULL; nsrr = NEXT(nsrr, link))
		if (ns_samename(nsrr->name, dname) == 1)
			return (nsrr);
	return (NULL);
}