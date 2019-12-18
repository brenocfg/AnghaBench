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
typedef  int u_int32_t ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;
typedef  int acl_perm_t ;

/* Variables and functions */
 int ACL_ADD_FILE ; 
 int ACL_ADD_SUBDIRECTORY ; 
 int ACL_APPEND_DATA ; 
 int ACL_DELETE ; 
 int ACL_DELETE_CHILD ; 
 int ACL_EXECUTE ; 
 int ACL_LIST_DIRECTORY ; 
 int ACL_READ_ACL ; 
 int ACL_READ_ATTRIBUTES ; 
 int ACL_READ_DATA ; 
 int ACL_READ_NAMED_ATTRS ; 
 int ACL_SYNCHRONIZE ; 
 int ACL_WRITE_ACL ; 
 int ACL_WRITE_ATTRIBUTES ; 
 int ACL_WRITE_DATA ; 
 int ACL_WRITE_NAMED_ATTRS ; 
 int ACL_WRITE_OWNER ; 
 int NFSERR_ATTRNOTSUPP ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int NFSV4ACE_ADDFILE ; 
 int NFSV4ACE_ADDSUBDIRECTORY ; 
 int NFSV4ACE_APPENDDATA ; 
 int NFSV4ACE_DELETE ; 
 int NFSV4ACE_DELETECHILD ; 
 int NFSV4ACE_EXECUTE ; 
 int NFSV4ACE_LISTDIRECTORY ; 
 int NFSV4ACE_READACL ; 
 int NFSV4ACE_READATTRIBUTES ; 
 int NFSV4ACE_READDATA ; 
 int NFSV4ACE_READNAMEDATTR ; 
 int NFSV4ACE_SEARCH ; 
 int NFSV4ACE_SYNCHRONIZE ; 
 int NFSV4ACE_WRITEACL ; 
 int NFSV4ACE_WRITEATTRIBUTES ; 
 int NFSV4ACE_WRITEDATA ; 
 int NFSV4ACE_WRITENAMEDATTR ; 
 int NFSV4ACE_WRITEOWNER ; 

__attribute__((used)) static int
nfsrv_acemasktoperm(u_int32_t acetype, u_int32_t mask, int owner,
    enum vtype type, acl_perm_t *permp)
{
	acl_perm_t perm = 0x0;
	int error = 0;

	if (mask & NFSV4ACE_READDATA) {
		mask &= ~NFSV4ACE_READDATA;
		perm |= ACL_READ_DATA;
	}
	if (mask & NFSV4ACE_LISTDIRECTORY) {
		mask &= ~NFSV4ACE_LISTDIRECTORY;
		perm |= ACL_LIST_DIRECTORY;
	}
	if (mask & NFSV4ACE_WRITEDATA) {
		mask &= ~NFSV4ACE_WRITEDATA;
		perm |= ACL_WRITE_DATA;
	}
	if (mask & NFSV4ACE_ADDFILE) {
		mask &= ~NFSV4ACE_ADDFILE;
		perm |= ACL_ADD_FILE;
	}
	if (mask & NFSV4ACE_APPENDDATA) {
		mask &= ~NFSV4ACE_APPENDDATA;
		perm |= ACL_APPEND_DATA;
	}
	if (mask & NFSV4ACE_ADDSUBDIRECTORY) {
		mask &= ~NFSV4ACE_ADDSUBDIRECTORY;
		perm |= ACL_ADD_SUBDIRECTORY;
	}
	if (mask & NFSV4ACE_READNAMEDATTR) {
		mask &= ~NFSV4ACE_READNAMEDATTR;
		perm |= ACL_READ_NAMED_ATTRS;
	}
	if (mask & NFSV4ACE_WRITENAMEDATTR) {
		mask &= ~NFSV4ACE_WRITENAMEDATTR;
		perm |= ACL_WRITE_NAMED_ATTRS;
	}
	if (mask & NFSV4ACE_EXECUTE) {
		mask &= ~NFSV4ACE_EXECUTE;
		perm |= ACL_EXECUTE;
	}
	if (mask & NFSV4ACE_SEARCH) {
		mask &= ~NFSV4ACE_SEARCH;
		perm |= ACL_EXECUTE;
	}
	if (mask & NFSV4ACE_DELETECHILD) {
		mask &= ~NFSV4ACE_DELETECHILD;
		perm |= ACL_DELETE_CHILD;
	}
	if (mask & NFSV4ACE_READATTRIBUTES) {
		mask &= ~NFSV4ACE_READATTRIBUTES;
		perm |= ACL_READ_ATTRIBUTES;
	}
	if (mask & NFSV4ACE_WRITEATTRIBUTES) {
		mask &= ~NFSV4ACE_WRITEATTRIBUTES;
		perm |= ACL_WRITE_ATTRIBUTES;
	}
	if (mask & NFSV4ACE_DELETE) {
		mask &= ~NFSV4ACE_DELETE;
		perm |= ACL_DELETE;
	}
	if (mask & NFSV4ACE_READACL) {
		mask &= ~NFSV4ACE_READACL;
		perm |= ACL_READ_ACL;
	}
	if (mask & NFSV4ACE_WRITEACL) {
		mask &= ~NFSV4ACE_WRITEACL;
		perm |= ACL_WRITE_ACL;
	}
	if (mask & NFSV4ACE_WRITEOWNER) {
		mask &= ~NFSV4ACE_WRITEOWNER;
		perm |= ACL_WRITE_OWNER;
	}
	if (mask & NFSV4ACE_SYNCHRONIZE) {
		mask &= ~NFSV4ACE_SYNCHRONIZE;
		perm |= ACL_SYNCHRONIZE;
	}
	if (mask != 0) {
		error = NFSERR_ATTRNOTSUPP;
		goto out;
	}
	*permp = perm;

out:
	NFSEXITCODE(error);
	return (error);
}