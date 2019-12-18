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

/* Variables and functions */
 int MNT_ACLS ; 
 int MNT_ASYNC ; 
 int MNT_EMPTYDIR ; 
 int MNT_MULTILABEL ; 
 int MNT_NFS4ACLS ; 
 int MNT_NOATIME ; 
 int MNT_NOCLUSTERR ; 
 int MNT_NOCLUSTERW ; 
 int MNT_NOCOVER ; 
 int MNT_NOEXEC ; 
 int MNT_NOSUID ; 
 int MNT_NOSYMFOLLOW ; 
 int MNT_RDONLY ; 
 int MNT_SUIDDIR ; 
 int MNT_SYNCHRONOUS ; 
 int MNT_UNION ; 
 int MNT_UNTRUSTED ; 
 char* catopt (char*,char*) ; 

char *
flags2opts(int flags)
{
	char *res;

	res = NULL;

	if (flags & MNT_RDONLY)		res = catopt(res, "ro");
	if (flags & MNT_SYNCHRONOUS)	res = catopt(res, "sync");
	if (flags & MNT_NOEXEC)		res = catopt(res, "noexec");
	if (flags & MNT_NOSUID)		res = catopt(res, "nosuid");
	if (flags & MNT_UNION)		res = catopt(res, "union");
	if (flags & MNT_ASYNC)		res = catopt(res, "async");
	if (flags & MNT_NOATIME)	res = catopt(res, "noatime");
	if (flags & MNT_NOCLUSTERR)	res = catopt(res, "noclusterr");
	if (flags & MNT_NOCLUSTERW)	res = catopt(res, "noclusterw");
	if (flags & MNT_NOSYMFOLLOW)	res = catopt(res, "nosymfollow");
	if (flags & MNT_SUIDDIR)	res = catopt(res, "suiddir");
	if (flags & MNT_MULTILABEL)	res = catopt(res, "multilabel");
	if (flags & MNT_ACLS)		res = catopt(res, "acls");
	if (flags & MNT_NFS4ACLS)	res = catopt(res, "nfsv4acls");
	if (flags & MNT_UNTRUSTED)	res = catopt(res, "untrusted");
	if (flags & MNT_NOCOVER)	res = catopt(res, "nocover");
	if (flags & MNT_EMPTYDIR)	res = catopt(res, "emptydir");

	return (res);
}