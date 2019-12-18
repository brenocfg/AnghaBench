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
struct TYPE_2__ {scalar_t__ n_type; scalar_t__ n_value; char* n_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kd ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_read (int /*<<< orphan*/ ,scalar_t__,void*,size_t) ; 
 TYPE_1__* namelist ; 
 int /*<<< orphan*/  xo_errx (int,char*,char const*,...) ; 

__attribute__((used)) static void
kreado(int nlx, void *addr, size_t size, size_t offset)
{
	const char *sym;

	if (namelist[nlx].n_type == 0 || namelist[nlx].n_value == 0) {
		sym = namelist[nlx].n_name;
		if (*sym == '_')
			++sym;
		xo_errx(1, "symbol %s not defined", sym);
	}
	if ((size_t)kvm_read(kd, namelist[nlx].n_value + offset, addr,
	    size) != size) {
		sym = namelist[nlx].n_name;
		if (*sym == '_')
			++sym;
		xo_errx(1, "%s: %s", sym, kvm_geterr(kd));
	}
}