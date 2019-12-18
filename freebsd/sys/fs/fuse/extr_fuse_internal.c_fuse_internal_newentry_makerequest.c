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
typedef  int /*<<< orphan*/  uint64_t ;
struct mount {int dummy; } ;
struct fuse_dispatcher {size_t iosize; char* indata; } ;
struct componentname {size_t cn_namelen; void* cn_nameptr; int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_thread; } ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;

/* Variables and functions */
 int /*<<< orphan*/  fdisp_make (struct fuse_dispatcher*,int,struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 

void
fuse_internal_newentry_makerequest(struct mount *mp,
    uint64_t dnid,
    struct componentname *cnp,
    enum fuse_opcode op,
    void *buf,
    size_t bufsize,
    struct fuse_dispatcher *fdip)
{
	fdip->iosize = bufsize + cnp->cn_namelen + 1;

	fdisp_make(fdip, op, mp, dnid, cnp->cn_thread, cnp->cn_cred);
	memcpy(fdip->indata, buf, bufsize);
	memcpy((char *)fdip->indata + bufsize, cnp->cn_nameptr, cnp->cn_namelen);
	((char *)fdip->indata)[bufsize + cnp->cn_namelen] = '\0';
}