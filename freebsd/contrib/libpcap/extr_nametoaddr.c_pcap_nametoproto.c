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
struct protoent_data {int dummy; } ;
struct protoent {int p_proto; } ;

/* Variables and functions */
 int PROTO_UNDEF ; 
 struct protoent* getprotobyname (char const*) ; 
 int getprotobyname_r (char const*,struct protoent*,char*,...) ; 

int
pcap_nametoproto(const char *str)
{
	struct protoent *p;
  #if defined(HAVE_LINUX_GETNETBYNAME_R)
	/*
	 * We have Linux's reentrant getprotobyname_r().
	 */
	struct protoent result_buf;
	char buf[1024];	/* arbitrary size */
	int err;

	err = getprotobyname_r(str, &result_buf, buf, sizeof buf, &p);
	if (err != 0) {
		/*
		 * XXX - dynamically allocate the buffer, and make it
		 * bigger if we get ERANGE back?
		 */
		return 0;
	}
  #elif defined(HAVE_SOLARIS_IRIX_GETNETBYNAME_R)
	/*
	 * We have Solaris's and IRIX's reentrant getprotobyname_r().
	 */
	struct protoent result_buf;
	char buf[1024];	/* arbitrary size */

	p = getprotobyname_r(str, &result_buf, buf, (int)sizeof buf);
  #elif defined(HAVE_AIX_GETNETBYNAME_R)
	/*
	 * We have AIX's reentrant getprotobyname_r().
	 */
	struct protoent result_buf;
	struct protoent_data proto_data;

	if (getprotobyname_r(str, &result_buf, &proto_data) == -1)
		p = NULL;
	else
		p = &result_buf;
  #else
 	/*
 	 * We don't have any getprotobyname_r(); either we have a
 	 * getprotobyname() that uses thread-specific data, in which
 	 * case we're thread-safe (sufficiently recent FreeBSD,
 	 * sufficiently recent Darwin-based OS, sufficiently recent
 	 * HP-UX, sufficiently recent Tru64 UNIX, Windows), or we have
	 * the traditional getprotobyname() (everything else, including
 	 * current NetBSD and OpenBSD), in which case we're not
 	 * thread-safe.
 	 */
	p = getprotobyname(str);
  #endif
	if (p != 0)
		return p->p_proto;
	else
		return PROTO_UNDEF;
}