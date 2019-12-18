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
struct procstat {int /*<<< orphan*/ * kd; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROCSTAT_KVM ; 
 int _POSIX2_LINE_MAX ; 
 struct procstat* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct procstat*) ; 
 int /*<<< orphan*/ * kvm_openfiles (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

struct procstat *
procstat_open_kvm(const char *nlistf, const char *memf)
{
	struct procstat *procstat;
	kvm_t *kd;
	char buf[_POSIX2_LINE_MAX];

	procstat = calloc(1, sizeof(*procstat));
	if (procstat == NULL) {
		warn("malloc()");
		return (NULL);
	}
	kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, buf);
	if (kd == NULL) {
		warnx("kvm_openfiles(): %s", buf);
		free(procstat);
		return (NULL);
	}
	procstat->type = PROCSTAT_KVM;
	procstat->kd = kd;
	return (procstat);
}