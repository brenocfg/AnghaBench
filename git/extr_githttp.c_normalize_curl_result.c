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
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_HTTP_RETURNED_ERROR ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  xsnprintf (char*,size_t,char*,long) ; 

void normalize_curl_result(CURLcode *result, long http_code,
			   char *errorstr, size_t errorlen)
{
	/*
	 * If we see a failing http code with CURLE_OK, we have turned off
	 * FAILONERROR (to keep the server's custom error response), and should
	 * translate the code into failure here.
	 *
	 * Likewise, if we see a redirect (30x code), that means we turned off
	 * redirect-following, and we should treat the result as an error.
	 */
	if (*result == CURLE_OK && http_code >= 300) {
		*result = CURLE_HTTP_RETURNED_ERROR;
		/*
		 * Normally curl will already have put the "reason phrase"
		 * from the server into curl_errorstr; unfortunately without
		 * FAILONERROR it is lost, so we can give only the numeric
		 * status code.
		 */
		xsnprintf(errorstr, errorlen,
			  "The requested URL returned error: %ld",
			  http_code);
	}
}