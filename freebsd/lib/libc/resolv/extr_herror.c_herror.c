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
struct iovec {char* iov_base; int iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_CONST (char const*,char*) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/ * __h_errno () ; 
 int /*<<< orphan*/  _writev (int /*<<< orphan*/ ,struct iovec*,int) ; 
 char* hstrerror (int /*<<< orphan*/ ) ; 
 void* strlen (char*) ; 

void
herror(const char *s) {
	struct iovec iov[4], *v = iov;
	char *t;

	if (s != NULL && *s != '\0') {
		DE_CONST(s, t);
		v->iov_base = t;
		v->iov_len = strlen(t);
		v++;
		DE_CONST(": ", t);
		v->iov_base = t;
		v->iov_len = 2;
		v++;
	}
	DE_CONST(hstrerror(*__h_errno()), t);
	v->iov_base = t;
	v->iov_len = strlen(v->iov_base);
	v++;
	DE_CONST("\n", t);
	v->iov_base = t;
	v->iov_len = 1;
	_writev(STDERR_FILENO, iov, (v - iov) + 1);
}