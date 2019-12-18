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
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 char* FormatError (scalar_t__) ; 
 char* GetWSAErrorMessage (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WSABASEERR ; 
 scalar_t__ _sys_nerr ; 
 char* strerror (scalar_t__) ; 

char *
NTstrerror(int err, BOOL *bfreebuf) {
	char *retmsg = NULL;

	/* Copy the error value first in case of other errors */	
	DWORD errval = err; 

	*bfreebuf = FALSE;

	/* Get the Winsock2 error messages */
	if (errval >= WSABASEERR && errval <= (WSABASEERR + 1015)) {
		retmsg = GetWSAErrorMessage(errval);
		if (retmsg != NULL)
			return (retmsg);
	}
	/*
	 * If it's not one of the standard Unix error codes,
	 * try a system error message
	 */
	if (errval > (DWORD) _sys_nerr) {
		*bfreebuf = TRUE;
		return (FormatError(errval));
	} else {
		return (strerror(errval));
	}
}