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
struct vmtotal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * kd ; 
 int /*<<< orphan*/  mysysctl (char*,struct vmtotal*,size_t*) ; 
 int /*<<< orphan*/  xo_errx (int,char*) ; 

__attribute__((used)) static void
fill_vmtotal(struct vmtotal *vmtp)
{
	size_t size;

	if (kd != NULL) {
		/* XXX fill vmtp */
		xo_errx(1, "not implemented");
	} else {
		size = sizeof(*vmtp);
		mysysctl("vm.vmtotal", vmtp, &size);
		if (size != sizeof(*vmtp))
			xo_errx(1, "vm.total size mismatch");
	}
}