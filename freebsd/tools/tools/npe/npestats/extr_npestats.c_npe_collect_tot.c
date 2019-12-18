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
struct npestatfoo_p {int /*<<< orphan*/  total; } ;
struct bsdstat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  npe_collect (struct npestatfoo_p*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
npe_collect_tot(struct bsdstat *sf)
{
	struct npestatfoo_p *wf = (struct npestatfoo_p *) sf;

	npe_collect(wf, &wf->total);
}