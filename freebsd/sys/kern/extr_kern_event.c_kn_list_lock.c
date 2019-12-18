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
struct knote {struct knlist* kn_knlist; } ;
struct knlist {int /*<<< orphan*/  kl_lockarg; int /*<<< orphan*/  (* kl_lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct knlist *
kn_list_lock(struct knote *kn)
{
	struct knlist *knl;

	knl = kn->kn_knlist;
	if (knl != NULL)
		knl->kl_lock(knl->kl_lockarg);
	return (knl);
}