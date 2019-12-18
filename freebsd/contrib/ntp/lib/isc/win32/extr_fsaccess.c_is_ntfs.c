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
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FSType ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetVolumeInformation (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ isc_file_absolutepath (char const*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strtok (char*,char*) ; 

BOOL
is_ntfs(const char * file) {

	char drive[255];
	char FSType[20];
	char tmpbuf[256];
	char *machinename;
	char *sharename;
	char filename[1024];

	REQUIRE(filename != NULL);

	if (isc_file_absolutepath(file, filename,
		sizeof(filename)) != ISC_R_SUCCESS) {
		return (FALSE);
	}

	/*
	 * Look for c:\path\... style, c:/path/... or \\computer\shar\path...
	 * the UNC style file specs
	 */
	if (isalpha(filename[0]) && filename[1] == ':' && 
		(filename[2] == '\\' || filename[2] == '/')) {
		strncpy(drive, filename, 3);
		drive[3] = '\0';
	}

	else if ((filename[0] == '\\') && (filename[1] == '\\')) {
		/* Find the machine and share name and rebuild the UNC */
		strcpy(tmpbuf, filename);
		machinename = strtok(tmpbuf, "\\");
		sharename = strtok(NULL, "\\");
		strcpy(drive, "\\\\");
		strcat(drive, machinename);
		strcat(drive, "\\");
		strcat(drive, sharename);
		strcat(drive, "\\");

	}
	else /* Not determinable */
		return (FALSE);
		
	GetVolumeInformation(drive, NULL, 0, NULL, 0, NULL, FSType,
			     sizeof(FSType));
	if(strcmp(FSType,"NTFS") == 0)
		return (TRUE);
	else
		return (FALSE);
}