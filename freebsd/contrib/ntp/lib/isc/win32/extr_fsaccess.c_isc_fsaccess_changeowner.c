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
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  groupBuffer ;
typedef  int /*<<< orphan*/  domainBuffer ;
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int GROUP_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  ISC_R_NOPERM ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LookupAccountName (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*,char*,int*,int /*<<< orphan*/ *) ; 
 int OWNER_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int /*<<< orphan*/  SetFileSecurity (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSecurityDescriptorGroup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetSecurityDescriptorOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ is_ntfs (char const*) ; 

isc_result_t
isc_fsaccess_changeowner(const char *filename, const char *user) {
	SECURITY_DESCRIPTOR psd;
	BYTE sidBuffer[500];
	BYTE groupBuffer[500];
	PSID psid=(PSID) &sidBuffer;
	DWORD sidBufferSize = sizeof(sidBuffer);
	char domainBuffer[100];
	DWORD domainBufferSize = sizeof(domainBuffer);
	SID_NAME_USE snu;
	PSID pSidGroup = (PSID) &groupBuffer;
	DWORD groupBufferSize = sizeof(groupBuffer);


	/*
	 * Determine if this is a FAT or NTFS disk and
	 * call the appropriate function to set the ownership
	 * FAT disks do not have ownership attributes so it's
	 * a noop.
	 */
	if (is_ntfs(filename) == FALSE)
		return (ISC_R_SUCCESS);

	if (!InitializeSecurityDescriptor(&psd, SECURITY_DESCRIPTOR_REVISION))
		return (ISC_R_NOPERM);

	if (!LookupAccountName(0, user, psid, &sidBufferSize, domainBuffer,
		&domainBufferSize, &snu))
		return (ISC_R_NOPERM);

	/* Make sure administrators can get to it */
	domainBufferSize = sizeof(domainBuffer);
	if (!LookupAccountName(0, "Administrators", pSidGroup,
		&groupBufferSize, domainBuffer, &domainBufferSize, &snu))
		return (ISC_R_NOPERM);

	if (!SetSecurityDescriptorOwner(&psd, psid, FALSE))
		return (ISC_R_NOPERM);

	if (!SetSecurityDescriptorGroup(&psd, pSidGroup, FALSE))
		return (ISC_R_NOPERM);

	if (!SetFileSecurity(filename,
		OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION,
		&psd))
		return (ISC_R_NOPERM);

	return (ISC_R_SUCCESS);
}