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
 int CURLE_FILE_COULDNT_READ_FILE ; 
 int CURLE_FTP_COULDNT_RETR_FILE ; 
 int CURLE_HTTP_RETURNED_ERROR ; 

__attribute__((used)) static inline int missing__target(int code, int result)
{
	return	/* file:// URL -- do we ever use one??? */
		(result == CURLE_FILE_COULDNT_READ_FILE) ||
		/* http:// and https:// URL */
		(code == 404 && result == CURLE_HTTP_RETURNED_ERROR) ||
		/* ftp:// URL */
		(code == 550 && result == CURLE_FTP_COULDNT_RETR_FILE)
		;
}