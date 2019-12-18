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
typedef  int /*<<< orphan*/  X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  HostnameValidationResult ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 scalar_t__ ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 scalar_t__ ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 scalar_t__ CURL_HOST_MATCH ; 
 scalar_t__ Curl_cert_hostcheck (char const*,char const*) ; 
 int /*<<< orphan*/  Error ; 
 int /*<<< orphan*/  MalformedCertificate ; 
 int /*<<< orphan*/  MatchFound ; 
 int /*<<< orphan*/  MatchNotFound ; 
 int /*<<< orphan*/  NID_commonName ; 
 int /*<<< orphan*/ * X509_NAME_ENTRY_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_get_entry (int /*<<< orphan*/ ,int) ; 
 int X509_NAME_get_index_by_NID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static HostnameValidationResult matches_common_name(const char *hostname, const X509 *server_cert) {
        int common_name_loc = -1;
        X509_NAME_ENTRY *common_name_entry = NULL;
        ASN1_STRING *common_name_asn1 = NULL;
        const char *common_name_str = NULL;

        // Find the position of the CN field in the Subject field of the certificate
        common_name_loc = X509_NAME_get_index_by_NID(X509_get_subject_name((X509 *) server_cert), NID_commonName, -1);
        if (common_name_loc < 0) {
                return Error;
        }

        // Extract the CN field
        common_name_entry = X509_NAME_get_entry(X509_get_subject_name((X509 *) server_cert), common_name_loc);
        if (common_name_entry == NULL) {
                return Error;
        }

        // Convert the CN field to a C string
        common_name_asn1 = X509_NAME_ENTRY_get_data(common_name_entry);
        if (common_name_asn1 == NULL) {
                return Error;
        }
        common_name_str = (char *) ASN1_STRING_get0_data(common_name_asn1);

        // Make sure there isn't an embedded NUL character in the CN
        if ((size_t)ASN1_STRING_length(common_name_asn1) != strlen(common_name_str)) {
                return MalformedCertificate;
        }

        // Compare expected hostname with the CN
        if (Curl_cert_hostcheck(common_name_str, hostname) == CURL_HOST_MATCH) {
                return MatchFound;
        }
        else {
                return MatchNotFound;
        }
}