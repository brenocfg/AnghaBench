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
struct msghdr {int msg_controllen; int /*<<< orphan*/ * msg_control; } ;
struct cmsghdr {int cmsg_len; } ;
typedef  int /*<<< orphan*/  magic ;
typedef  int /*<<< orphan*/  cmh ;
typedef  int /*<<< orphan*/ * caddr_t ;
typedef  int /*<<< orphan*/  ancbuf ;

/* Variables and functions */
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 void* CMSG_LEN (int /*<<< orphan*/ ) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int CMSG_SPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 
 int /*<<< orphan*/  checkptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  checkstr (char const*,char const*,int,char*) ; 
 int /*<<< orphan*/  init_hdrs (struct msghdr*,struct cmsghdr*,char*,int) ; 
 int /*<<< orphan*/  set_funcname (char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

void
test_cmsg_nexthdr()
{
	struct msghdr  mh;
	struct cmsghdr cmh;
	struct cmsghdr *cmhp, *cmhnextp;
	char ancbuf[10240];
	char magic[] = "MAGIC";

	set_funcname("test_cmsg_nexthdr", sizeof("test_cmsg_nexthdr"));

	/*
	 * Test: More than one cmsghdr
	 */
	init_hdrs(&mh, &cmh, ancbuf, sizeof(ancbuf));
	mh.msg_control = (caddr_t)ancbuf;
	mh.msg_controllen  = CMSG_SPACE(0) * 2;	/* 2 cmsghdr with no data */
	cmh.cmsg_len = CMSG_LEN(0);

	/* 
	 * Copy the same instance of cmsghdr twice. Use a magic value
	 * to id the second copy.
	 */
	bcopy((void *)&cmh, (void *)ancbuf, sizeof(cmh));
	strlcpy((char *)&cmh, (const char *)&magic, sizeof(magic));
	bcopy((void *)&cmh,
	    (void *)((caddr_t)ancbuf + CMSG_SPACE(0)),
	    sizeof(cmh));
	cmhp = CMSG_FIRSTHDR(&mh);
	cmhnextp = CMSG_NXTHDR(&mh, cmhp);
	checkstr((const char *)&magic, (const char *)cmhnextp, sizeof(magic),
	    "more than one cmsghdr\0");

	/*
	 * Test: only one cmsghdr
	 */
	init_hdrs(&mh, &cmh, ancbuf, sizeof(ancbuf));
	mh.msg_control = (caddr_t)ancbuf;
	mh.msg_controllen  = CMSG_SPACE(0);
	cmh.cmsg_len = CMSG_LEN(0);
	bcopy((void *)&cmh, (void *)ancbuf, sizeof(cmh));
	cmhp = CMSG_FIRSTHDR(&mh);
	cmhnextp = CMSG_NXTHDR(&mh, cmhp);
	checkptr(NULL, (caddr_t)cmhnextp, "only one cmsghdr\0");

	/*
	 * Test: NULL cmsg pointer
	 */
	init_hdrs(&mh, &cmh, ancbuf, sizeof(ancbuf));
	mh.msg_control = (caddr_t)ancbuf;
	mh.msg_controllen  = sizeof(ancbuf);
	cmh.cmsg_len = sizeof(ancbuf);
	bcopy((void *)&cmh, (void *)ancbuf, sizeof(cmh));
	cmhp = CMSG_FIRSTHDR(&mh);
	cmhnextp = CMSG_NXTHDR(&mh, NULL);
	checkptr((caddr_t)cmhp, (caddr_t)cmhnextp, "null second argument\0");
}