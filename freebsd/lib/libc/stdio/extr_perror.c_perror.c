#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iovec {char* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  msgbuf ;
struct TYPE_4__ {int /*<<< orphan*/  _flags; int /*<<< orphan*/  _file; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int NL_TEXTMAX ; 
 int /*<<< orphan*/  __SOFF ; 
 int /*<<< orphan*/  __sflush (TYPE_1__*) ; 
 int /*<<< orphan*/  _writev (int /*<<< orphan*/ ,struct iovec*,int) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* stderr ; 
 int /*<<< orphan*/  strerror_r (int /*<<< orphan*/ ,char*,int) ; 
 void* strlen (char const*) ; 

void
perror(const char *s)
{
	char msgbuf[NL_TEXTMAX];
	struct iovec *v;
	struct iovec iov[4];

	v = iov;
	if (s != NULL && *s != '\0') {
		v->iov_base = (char *)s;
		v->iov_len = strlen(s);
		v++;
		v->iov_base = ": ";
		v->iov_len = 2;
		v++;
	}
	strerror_r(errno, msgbuf, sizeof(msgbuf));
	v->iov_base = msgbuf;
	v->iov_len = strlen(v->iov_base);
	v++;
	v->iov_base = "\n";
	v->iov_len = 1;
	FLOCKFILE_CANCELSAFE(stderr);
	__sflush(stderr);
	(void)_writev(stderr->_file, iov, (v - iov) + 1);
	stderr->_flags &= ~__SOFF;
	FUNLOCKFILE_CANCELSAFE();
}