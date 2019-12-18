#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_4__ {int /*<<< orphan*/  grui0_name; int /*<<< orphan*/  lgrui0_name; } ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  TYPE_1__* LPLOCALGROUP_USERS_INFO_0 ;
typedef  TYPE_1__* LPGROUP_USERS_INFO_0 ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_NOPERM ; 
 int /*<<< orphan*/  ISC_R_NOSPACE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 scalar_t__ LG_INCLUDE_INDIRECT ; 
 int MAX_NAME_LENGTH ; 
 scalar_t__ MAX_PREFERRED_LENGTH ; 
 scalar_t__ NERR_Success ; 
 scalar_t__ NERR_UserNotFound ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 scalar_t__ NetUserGetGroups (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ NetUserGetLocalGroups (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 size_t mbstowcs (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t wcslen (int /*<<< orphan*/ ) ; 
 size_t wcstombs (char*,int /*<<< orphan*/ ,size_t) ; 

isc_result_t
isc_ntsecurity_getaccountgroups(char *username, char **GroupList,
				unsigned int maxgroups,
				unsigned int *totalGroups) {
	LPGROUP_USERS_INFO_0 pTmpBuf;
	LPLOCALGROUP_USERS_INFO_0 pTmpLBuf;
	DWORD i;
	LPLOCALGROUP_USERS_INFO_0 pBuf = NULL;
	LPGROUP_USERS_INFO_0 pgrpBuf = NULL;
	DWORD dwLevel = 0;
	DWORD dwFlags = LG_INCLUDE_INDIRECT;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	NET_API_STATUS nStatus;
	DWORD dwTotalCount = 0;
	size_t retlen;
	wchar_t user[MAX_NAME_LENGTH];

	retlen = mbstowcs(user, username, MAX_NAME_LENGTH);

	*totalGroups = 0;
	/*
	 * Call the NetUserGetLocalGroups function
	 * specifying information level 0.
	 *
	 * The LG_INCLUDE_INDIRECT flag specifies that the
	 * function should also return the names of the local
	 * groups in which the user is indirectly a member.
	 */
	nStatus = NetUserGetLocalGroups(NULL,
				   user,
				   dwLevel,
				   dwFlags,
				   (LPBYTE *) &pBuf,
				   dwPrefMaxLen,
				   &dwEntriesRead,
				   &dwTotalEntries);
	/*
	 * See if the call succeeds,
	 */
	if (nStatus != NERR_Success) {
		if (nStatus == ERROR_ACCESS_DENIED)
			return (ISC_R_NOPERM);
		if (nStatus == ERROR_MORE_DATA)
			return (ISC_R_NOSPACE);
		if (nStatus == NERR_UserNotFound)
			dwEntriesRead = 0;
	}

	dwTotalCount = 0;
	if (pBuf != NULL) {
		pTmpLBuf = pBuf;
		/*
		 * Loop through the entries
		 */
		 for (i = 0;
		     (i < dwEntriesRead && *totalGroups < maxgroups); i++) {
			assert(pTmpLBuf != NULL);
			if (pTmpLBuf == NULL)
				break;
			retlen = wcslen(pTmpLBuf->lgrui0_name);
			GroupList[*totalGroups] = (char *) malloc(retlen +1);
			if (GroupList[*totalGroups] == NULL)
				return (ISC_R_NOMEMORY);

			retlen = wcstombs(GroupList[*totalGroups],
				 pTmpLBuf->lgrui0_name, retlen);
			GroupList[*totalGroups][retlen] = '\0';
			if (strcmp(GroupList[*totalGroups], "None") == 0)
				free(GroupList[*totalGroups]);
			else
				(*totalGroups)++;
			pTmpLBuf++;
		}
	}
	/* Free the allocated memory. */
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);


	/*
	 * Call the NetUserGetGroups function, specifying level 0.
	 */
	nStatus = NetUserGetGroups(NULL,
			      user,
			      dwLevel,
			      (LPBYTE*)&pgrpBuf,
			      dwPrefMaxLen,
			      &dwEntriesRead,
			      &dwTotalEntries);
	/*
	 * See if the call succeeds,
	 */
	if (nStatus != NERR_Success) {
		if (nStatus == ERROR_ACCESS_DENIED)
			return (ISC_R_NOPERM);
		if (nStatus == ERROR_MORE_DATA)
			return (ISC_R_NOSPACE);
		if (nStatus == NERR_UserNotFound)
			dwEntriesRead = 0;
	}

	if (pgrpBuf != NULL) {
		pTmpBuf = pgrpBuf;
		/*
		 * Loop through the entries
		 */
		 for (i = 0;
		     (i < dwEntriesRead && *totalGroups < maxgroups); i++) {
			assert(pTmpBuf != NULL);

			if (pTmpBuf == NULL)
				break;
			retlen = wcslen(pTmpBuf->grui0_name);
			GroupList[*totalGroups] = (char *) malloc(retlen +1);
			if (GroupList[*totalGroups] == NULL)
				return (ISC_R_NOMEMORY);

			retlen = wcstombs(GroupList[*totalGroups],
				 pTmpBuf->grui0_name, retlen);
			GroupList[*totalGroups][retlen] = '\0';
			if (strcmp(GroupList[*totalGroups], "None") == 0)
				free(GroupList[*totalGroups]);
			else
				(*totalGroups)++;
			pTmpBuf++;
		}
	}
	/*
	 * Free the allocated memory.
	 */
	if (pgrpBuf != NULL)
		NetApiBufferFree(pgrpBuf);

	return (ISC_R_SUCCESS);
}