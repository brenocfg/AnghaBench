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
struct thread {int dummy; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG_TEXT (char*) ; 
 int /*<<< orphan*/  AUDIT_ARG_VALUE (int) ; 
 int EXTATTR_MAXNAMELEN ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*,struct thread*) ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int copyinstr (char const*,char*,int,int /*<<< orphan*/ *) ; 
 int extattr_delete_vp (int /*<<< orphan*/ ,int,char*,struct thread*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kern_extattr_delete_path(struct thread *td, const char *path, int attrnamespace,
    const char *uattrname, int follow)
{
	struct nameidata nd;
	char attrname[EXTATTR_MAXNAMELEN];
	int error;

	AUDIT_ARG_VALUE(attrnamespace);
	error = copyinstr(uattrname, attrname, EXTATTR_MAXNAMELEN, NULL);
	if (error)
		return(error);
	AUDIT_ARG_TEXT(attrname);

	NDINIT(&nd, LOOKUP, follow | AUDITVNODE1, UIO_USERSPACE, path, td);
	error = namei(&nd);
	if (error)
		return(error);
	NDFREE(&nd, NDF_ONLY_PNBUF);

	error = extattr_delete_vp(nd.ni_vp, attrnamespace, attrname, td);
	vrele(nd.ni_vp);
	return(error);
}