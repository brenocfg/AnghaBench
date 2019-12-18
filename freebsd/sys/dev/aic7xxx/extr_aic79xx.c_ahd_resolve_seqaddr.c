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
typedef  scalar_t__ u_int ;
struct patch {int dummy; } ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ahd_check_patch (struct ahd_softc*,struct patch**,scalar_t__,scalar_t__*) ; 
 struct patch* patches ; 

__attribute__((used)) static u_int
ahd_resolve_seqaddr(struct ahd_softc *ahd, u_int address)
{
	struct patch *cur_patch;
	int address_offset;
	u_int skip_addr;
	u_int i;

	address_offset = 0;
	cur_patch = patches;
	skip_addr = 0;

	for (i = 0; i < address;) {

		ahd_check_patch(ahd, &cur_patch, i, &skip_addr);

		if (skip_addr > i) {
			int end_addr;

			end_addr = MIN(address, skip_addr);
			address_offset += end_addr - i;
			i = skip_addr;
		} else {
			i++;
		}
	}
	return (address - address_offset);
}