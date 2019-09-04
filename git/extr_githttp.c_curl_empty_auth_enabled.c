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
 scalar_t__ curl_empty_auth ; 

__attribute__((used)) static int curl_empty_auth_enabled(void)
{
	if (curl_empty_auth >= 0)
		return curl_empty_auth;

#ifndef LIBCURL_CAN_HANDLE_AUTH_ANY
	/*
	 * Our libcurl is too old to do AUTH_ANY in the first place;
	 * just default to turning the feature off.
	 */
#else
	/*
	 * In the automatic case, kick in the empty-auth
	 * hack as long as we would potentially try some
	 * method more exotic than "Basic" or "Digest".
	 *
	 * But only do this when this is our second or
	 * subsequent request, as by then we know what
	 * methods are available.
	 */
	if (http_auth_methods_restricted &&
	    (http_auth_methods & ~empty_auth_useless))
		return 1;
#endif
	return 0;
}