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
typedef  int /*<<< orphan*/  sidBuffer ;
typedef  int /*<<< orphan*/  otherSidBuffer ;
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  scalar_t__ isc_boolean_t ;
typedef  int /*<<< orphan*/  domainBuffer ;
typedef  int /*<<< orphan*/  adminSidBuffer ;
typedef  int /*<<< orphan*/  aclBuffer ;
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/  PACL ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_REVISION ; 
 int /*<<< orphan*/  AddAccessAllowedAce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DACL_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ADD_FILE ; 
 int FILE_ADD_SUBDIRECTORY ; 
 int FILE_ALL_ACCESS ; 
 int FILE_DELETE_CHILD ; 
 int FILE_GENERIC_EXECUTE ; 
 int FILE_GENERIC_READ ; 
 int FILE_GENERIC_WRITE ; 
 int FILE_LIST_DIRECTORY ; 
 int FILE_TRAVERSE ; 
 int GetLastError () ; 
 int ISC_FSACCESS_ACCESSCHILD ; 
 int ISC_FSACCESS_CREATECHILD ; 
 int ISC_FSACCESS_DELETECHILD ; 
 int ISC_FSACCESS_EXECUTE ; 
 int ISC_FSACCESS_LISTDIRECTORY ; 
 int ISC_FSACCESS_READ ; 
 int ISC_FSACCESS_WRITE ; 
 int /*<<< orphan*/  ISC_R_NOPERM ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 scalar_t__ ISC_TRUE ; 
 int /*<<< orphan*/  InitializeAcl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LookupAccountName (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*,char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int STANDARD_RIGHTS_ALL ; 
 int STEP ; 
 int /*<<< orphan*/  SetFileSecurity (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSecurityDescriptorDacl (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

isc_result_t
NTFS_Access_Control(const char *filename, const char *user, int access,
		    isc_boolean_t isdir) {
	SECURITY_DESCRIPTOR sd;
	BYTE aclBuffer[1024];
	PACL pacl=(PACL)&aclBuffer;
	BYTE sidBuffer[100];
	PSID psid=(PSID) &sidBuffer;
	DWORD sidBufferSize = sizeof(sidBuffer);
	BYTE adminSidBuffer[100];
	PSID padminsid=(PSID) &adminSidBuffer;
	DWORD adminSidBufferSize = sizeof(adminSidBuffer);
	BYTE otherSidBuffer[100];
	PSID pothersid=(PSID) &otherSidBuffer;
	DWORD otherSidBufferSize = sizeof(otherSidBuffer);
	char domainBuffer[100];
	DWORD domainBufferSize = sizeof(domainBuffer);
	SID_NAME_USE snu;
	int errval;
	DWORD NTFSbits;
	int caccess;


	/* Initialize an ACL */
	if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
		return (ISC_R_NOPERM);
	if (!InitializeAcl(pacl, sizeof(aclBuffer), ACL_REVISION))
		return (ISC_R_NOPERM);
	if (!LookupAccountName(0, user, psid, &sidBufferSize, domainBuffer,
			  &domainBufferSize, &snu))
		return (ISC_R_NOPERM);
	domainBufferSize = sizeof(domainBuffer);
	if (!LookupAccountName(0, "Administrators", padminsid,
		&adminSidBufferSize, domainBuffer, &domainBufferSize, &snu)) {
		errval = GetLastError();
		return (ISC_R_NOPERM);
	}
	domainBufferSize = sizeof(domainBuffer);
	if (!LookupAccountName(0, "Everyone", pothersid,
		&otherSidBufferSize, domainBuffer, &domainBufferSize, &snu)) {
		errval = GetLastError();
		return (ISC_R_NOPERM);
	}

	caccess = access;
	/* Owner check */

	NTFSbits = 0;
	if (caccess & ISC_FSACCESS_READ)
		NTFSbits |= FILE_GENERIC_READ;
	if (caccess & ISC_FSACCESS_WRITE)
		NTFSbits |= FILE_GENERIC_WRITE;
	if (caccess & ISC_FSACCESS_EXECUTE)
		NTFSbits |= FILE_GENERIC_EXECUTE;

	/* For directories check the directory-specific bits */
	if (isdir == ISC_TRUE) {
		if (caccess & ISC_FSACCESS_CREATECHILD)
			NTFSbits |= FILE_ADD_SUBDIRECTORY | FILE_ADD_FILE;
		if (caccess & ISC_FSACCESS_DELETECHILD)
			NTFSbits |= FILE_DELETE_CHILD;
		if (caccess & ISC_FSACCESS_LISTDIRECTORY)
			NTFSbits |= FILE_LIST_DIRECTORY;
		if (caccess & ISC_FSACCESS_ACCESSCHILD)
			NTFSbits |= FILE_TRAVERSE;
	}

	if (NTFSbits == (FILE_GENERIC_READ | FILE_GENERIC_WRITE
		     | FILE_GENERIC_EXECUTE))
		     NTFSbits |= FILE_ALL_ACCESS;
	/*
	 * Owner and Administrator also get STANDARD_RIGHTS_ALL
	 * to ensure that they have full control
	 */

	NTFSbits |= STANDARD_RIGHTS_ALL;

	/* Add the ACE to the ACL */
	if (!AddAccessAllowedAce(pacl, ACL_REVISION, NTFSbits, psid))
		return (ISC_R_NOPERM);
	if (!AddAccessAllowedAce(pacl, ACL_REVISION, NTFSbits, padminsid))
		return (ISC_R_NOPERM);

	/*
	 * Group is ignored since we can be in multiple groups or no group
	 * and its meaning is not clear on Win32
	 */

	caccess = caccess >> STEP;

	/*
	 * Other check.  We translate this to be the same as Everyone
	 */

	caccess = caccess >> STEP;

	NTFSbits = 0;
	if (caccess & ISC_FSACCESS_READ)
		NTFSbits |= FILE_GENERIC_READ;
	if (caccess & ISC_FSACCESS_WRITE)
		NTFSbits |= FILE_GENERIC_WRITE;
	if (caccess & ISC_FSACCESS_EXECUTE)
		NTFSbits |= FILE_GENERIC_EXECUTE;

	/* For directories check the directory-specific bits */
	if (isdir == TRUE) {
		if (caccess & ISC_FSACCESS_CREATECHILD)
			NTFSbits |= FILE_ADD_SUBDIRECTORY | FILE_ADD_FILE;
		if (caccess & ISC_FSACCESS_DELETECHILD)
			NTFSbits |= FILE_DELETE_CHILD;
		if (caccess & ISC_FSACCESS_LISTDIRECTORY)
			NTFSbits |= FILE_LIST_DIRECTORY;
		if (caccess & ISC_FSACCESS_ACCESSCHILD)
			NTFSbits |= FILE_TRAVERSE;
	}
	/* Add the ACE to the ACL */
	if (!AddAccessAllowedAce(pacl, ACL_REVISION, NTFSbits,
				 pothersid))
		return (ISC_R_NOPERM);

	if (!SetSecurityDescriptorDacl(&sd, TRUE, pacl, FALSE))
		return (ISC_R_NOPERM);
	if (!SetFileSecurity(filename, DACL_SECURITY_INFORMATION, &sd)) {
		return (ISC_R_NOPERM);
	}

	return(ISC_R_SUCCESS);
}