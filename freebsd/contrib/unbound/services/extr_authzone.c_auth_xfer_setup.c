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
struct auth_zone {int dummy; } ;
struct auth_xfer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfr_find_soa (struct auth_zone*,struct auth_xfer*) ; 

__attribute__((used)) static int
auth_xfer_setup(struct auth_zone* z, struct auth_xfer* x)
{
	/* for a zone without zone transfers, x==NULL, so skip them,
	 * i.e. the zone config is fixed with no masters or urls */
	if(!z || !x) return 1;
	if(!xfr_find_soa(z, x)) {
		return 1;
	}
	/* nothing for probe, nextprobe and transfer tasks */
	return 1;
}