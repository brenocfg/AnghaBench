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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  kvm_t ;
struct TYPE_2__ {char const* n_name; int /*<<< orphan*/  n_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t) ; 
 TYPE_1__* namelist ; 
 int sysctlbyname (char const*,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,unsigned long,...) ; 

__attribute__((used)) static int
readvar(kvm_t *kd, const char *name, int nlid, void *ptr, size_t len)
{
	if (kd != NULL) {
		ssize_t nbytes;

		nbytes = kvm_read(kd, namelist[nlid].n_value, ptr, len);

		if (nbytes < 0) {
			warnx("kvm_read(%s): %s", namelist[nlid].n_name,
			    kvm_geterr(kd));
			return (1);
		} else if ((size_t)nbytes != len) {
			warnx("kvm_read(%s): expected %zu bytes, got %zd bytes",
			      namelist[nlid].n_name, len, nbytes);
			return (1);
		}
	} else {
		size_t nlen = len;

		if (sysctlbyname(name, ptr, &nlen, NULL, 0) == -1) {
			warn("sysctl(%s...) failed", name);
			return (1);
		}
		if (nlen != len) {
			warnx("sysctl(%s...): expected %lu, got %lu", name,
			      (unsigned long)len, (unsigned long)nlen);
			return (1);
		}
	}
	return (0);
}