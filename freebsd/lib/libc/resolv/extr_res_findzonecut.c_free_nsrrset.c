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
typedef  int /*<<< orphan*/  rrset_ns ;
typedef  int /*<<< orphan*/  rr_ns ;

/* Variables and functions */
 int /*<<< orphan*/ * HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_nsrr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_nsrrset(rrset_ns *nsrrsp) {
	rr_ns *nsrr;

	while ((nsrr = HEAD(*nsrrsp)) != NULL)
		free_nsrr(nsrrsp, nsrr);
}