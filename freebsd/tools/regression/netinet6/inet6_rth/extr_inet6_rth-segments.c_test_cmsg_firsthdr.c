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
struct cmsghdr {int dummy; } ;
typedef  int /*<<< orphan*/  magic ;
typedef  int /*<<< orphan*/  cmh ;
typedef  void* caddr_t ;
typedef  int /*<<< orphan*/  ancbuf ;

/* Variables and functions */
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 
 int /*<<< orphan*/  checkptr (int /*<<< orphan*/ *,void*,char*) ; 
 int /*<<< orphan*/  checkstr (char const*,char const*,int,char*) ; 
 int /*<<< orphan*/  init_hdrs (struct msghdr*,struct cmsghdr*,char*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_funcname (char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

void
test_cmsg_firsthdr()
{
	struct msghdr  mh;
	struct cmsghdr cmh;
	struct cmsghdr *cmhp;
	char ancbuf[1024];
	char magic[] = "MAGIC";

	set_funcname("test_cmsg_firsthdr", sizeof("test_cmsg_firsthdr"));

	/* CMSG_FIRSTHDR() where msg_control is NULL */
	init_hdrs(&mh, NULL, NULL, 0);
	mh.msg_control = NULL;
	cmhp = CMSG_FIRSTHDR(&mh);
	checkptr(NULL, (caddr_t)cmhp,
	    "msg_control is NULL\0");

	/* - where msg_controllen < sizeof cmsghdr */
	init_hdrs(&mh, NULL, NULL, 0);
	mh.msg_control = (caddr_t)&cmh;
	mh.msg_controllen = sizeof(cmh) - 1;
	cmhp = CMSG_FIRSTHDR(&mh);
	checkptr(NULL, (caddr_t)cmhp,
	    "msg_controllen < sizeof cmsghdr\0");

	/* - where msg_controllen == 0 */
	init_hdrs(&mh, NULL, NULL, 0);
	mh.msg_control = (caddr_t)&cmh;
	mh.msg_controllen = 0;
	cmhp = CMSG_FIRSTHDR(&mh);
	checkptr(NULL, (caddr_t)cmhp,
	    "msg_controllen == 0\0");

	/* no errors */
	init_hdrs(&mh, &cmh, ancbuf, sizeof(ancbuf));
	memset((void *)ancbuf, 0, sizeof(ancbuf));
	mh.msg_control = (caddr_t)ancbuf;
	mh.msg_controllen  = sizeof(ancbuf);
	strlcpy((char *)&cmh, (const char *)&magic, sizeof(magic));
	bcopy((void *)&cmh, (void *)ancbuf, sizeof(cmh));
	cmhp = CMSG_FIRSTHDR(&mh);
	checkstr((const char *)&magic, (const char *)cmhp, sizeof(magic),
	    "with payload\0");
}