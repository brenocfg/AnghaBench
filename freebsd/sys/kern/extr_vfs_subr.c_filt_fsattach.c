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
struct knote {int /*<<< orphan*/  kn_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_CLEAR ; 
 int /*<<< orphan*/  fs_knlist ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_fsattach(struct knote *kn)
{

	kn->kn_flags |= EV_CLEAR;
	knlist_add(&fs_knlist, kn, 0);
	return (0);
}