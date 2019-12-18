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
struct nlist {scalar_t__ n_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_nlist (int /*<<< orphan*/ *,struct nlist*) ; 
 int /*<<< orphan*/ * kvmd ; 
 scalar_t__ kvmd_init () ; 
 scalar_t__ nlistf ; 
 int /*<<< orphan*/  xo_errx (int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
kresolve_list(struct nlist *_nl)
{

	if ((kvmd == NULL) && (kvmd_init() != 0))
		return (-1);

	if (_nl[0].n_type != 0)
		return (0);

	if (kvm_nlist(kvmd, _nl) < 0) {
		if (nlistf)
			xo_errx(1, "%s: kvm_nlist: %s", nlistf,
			    kvm_geterr(kvmd));
		else
			xo_errx(1, "kvm_nlist: %s", kvm_geterr(kvmd));
	}

	return (0);
}