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
typedef  int /*<<< orphan*/  uint8_t ;
struct regional {int dummy; } ;
struct delegpt {scalar_t__ name; int /*<<< orphan*/  namelen; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  dp_type_mlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 scalar_t__ regional_alloc_init (struct regional*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int 
delegpt_set_name(struct delegpt* dp, struct regional* region, uint8_t* name)
{
	log_assert(!dp->dp_type_mlc);
	dp->namelabs = dname_count_size_labels(name, &dp->namelen);
	dp->name = regional_alloc_init(region, name, dp->namelen);
	return dp->name != 0;
}