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
struct mwlstatfoo_p {int /*<<< orphan*/  total; } ;
struct bsdstat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwl_collect (struct mwlstatfoo_p*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwl_collect_tot(struct bsdstat *sf)
{
	struct mwlstatfoo_p *wf = (struct mwlstatfoo_p *) sf;

	mwl_collect(wf, &wf->total);
}