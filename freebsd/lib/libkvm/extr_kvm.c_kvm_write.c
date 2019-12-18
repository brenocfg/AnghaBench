#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_9__ {int /*<<< orphan*/  program; int /*<<< orphan*/  pmfd; TYPE_1__* arch; int /*<<< orphan*/  vmfd; int /*<<< orphan*/  writable; } ;
typedef  TYPE_2__ kvm_t ;
struct TYPE_8__ {int (* ka_kvatop ) (TYPE_2__*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ ISALIVE (TYPE_2__*) ; 
 char* _PATH_MEM ; 
 int /*<<< orphan*/  _kvm_err (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _kvm_syserr (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int write (int /*<<< orphan*/ ,char const*,int) ; 

ssize_t
kvm_write(kvm_t *kd, u_long kva, const void *buf, size_t len)
{
	int cc;
	ssize_t cw;
	off_t pa;
	const char *cp;

	if (!ISALIVE(kd) && !kd->writable) {
		_kvm_err(kd, kd->program,
		    "kvm_write not implemented for dead kernels");
		return (-1);
	}

	if (ISALIVE(kd)) {
		/*
		 * Just like kvm_read, only we write.
		 */
		errno = 0;
		if (lseek(kd->vmfd, (off_t)kva, 0) == -1 && errno != 0) {
			_kvm_err(kd, 0, "invalid address (%lx)", kva);
			return (-1);
		}
		cc = write(kd->vmfd, buf, len);
		if (cc < 0) {
			_kvm_syserr(kd, 0, "kvm_write");
			return (-1);
		} else if ((size_t)cc < len)
			_kvm_err(kd, kd->program, "short write");
		return (cc);
	}

	cp = buf;
	while (len > 0) {
		cc = kd->arch->ka_kvatop(kd, kva, &pa);
		if (cc == 0)
			return (-1);
		if (cc > (ssize_t)len)
			cc = len;
		errno = 0;
		if (lseek(kd->pmfd, pa, 0) == -1 && errno != 0) {
			_kvm_syserr(kd, 0, _PATH_MEM);
			break;
		}
		cw = write(kd->pmfd, cp, cc);
		if (cw < 0) {
			_kvm_syserr(kd, kd->program, "kvm_write");
			break;
		}
		/*
		 * If ka_kvatop returns a bogus value or our core file is
		 * truncated, we might wind up seeking beyond the end of the
		 * core file in which case the read will return 0 (EOF).
		 */
		if (cw == 0)
			break;
		cp += cw;
		kva += cw;
		len -= cw;
	}

	return (cp - (const char *)buf);
}