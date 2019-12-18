#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kvm_t ;
struct TYPE_3__ {scalar_t__ n_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  kvm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_nlist (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * kvm_openfiles (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* nl ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static kvm_t *
kopen(char const *memf)
{
	kvm_t	*kvmd = NULL;
	char	 errbuf[_POSIX2_LINE_MAX];

	kvmd = kvm_openfiles(NULL, memf, NULL, O_RDONLY, errbuf);
	if (setgid(getgid()) != 0)
		err(1, "setgid");
	if (kvmd == NULL) {
		warnx("kvm_openfiles: %s", errbuf);
		return (NULL);
	}

	if (kvm_nlist(kvmd, nl) < 0) {
		warnx("kvm_nlist: %s", kvm_geterr(kvmd));
		goto fail;
	}

	if (nl[0].n_type == 0) {
		warnx("kvm_nlist: no namelist");
		goto fail;
	}

	return (kvmd);
fail:
	kvm_close(kvmd);

	return (NULL);
}