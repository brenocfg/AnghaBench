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
typedef  int /*<<< orphan*/  X509 ;
typedef  scalar_t__ HostnameValidationResult ;

/* Variables and functions */
 scalar_t__ Error ; 
 scalar_t__ NoSANPresent ; 
 scalar_t__ matches_common_name (char const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ matches_subject_alternative_name (char const*,int /*<<< orphan*/  const*) ; 

HostnameValidationResult validate_hostname(const char *hostname, const X509 *server_cert) {
	HostnameValidationResult result;

	if((hostname == NULL) || (server_cert == NULL))
		return Error;

	// First try the Subject Alternative Names extension
	result = matches_subject_alternative_name(hostname, server_cert);
	if (result == NoSANPresent) {
		// Extension was not found: try the Common Name
		result = matches_common_name(hostname, server_cert);
	}

	return result;
}