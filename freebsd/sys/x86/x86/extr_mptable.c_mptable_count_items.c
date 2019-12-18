#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int config_type; } ;

/* Variables and functions */
 TYPE_1__* mpfps ; 
 int /*<<< orphan*/  mptable_count_items_handler ; 
 int mptable_maxbusid ; 
 int mptable_nbusses ; 
 int mptable_nioapics ; 
 int /*<<< orphan*/  mptable_walk_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static void
mptable_count_items(void)
{

	/* Is this a pre-defined config? */
	if (mpfps->config_type != 0) {
		mptable_nioapics = 1;
		switch (mpfps->config_type) {
		case 1:
		case 2:
		case 3:
		case 4:
			mptable_nbusses = 1;
			break;
		case 5:
		case 6:
		case 7:
			mptable_nbusses = 2;
			break;
		default:
			panic("Unknown pre-defined MP Table config type %d",
			    mpfps->config_type);
		}
		mptable_maxbusid = mptable_nbusses - 1;
	} else
		mptable_walk_table(mptable_count_items_handler, NULL);
}