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
typedef  int /*<<< orphan*/  gnutls_x509_crt_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_strchr (char const*,char) ; 
 char* os_strdup (char const*) ; 
 char* str_token (char*,char*,char**) ; 
 int tls_match_suffix_helper (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int tls_match_suffix(gnutls_x509_crt_t cert, const char *match,
			    int full)
{
	char *values, *token, *context = NULL;
	int ret = 0;

	if (!os_strchr(match, ';'))
		return tls_match_suffix_helper(cert, match, full);

	values = os_strdup(match);
	if (!values)
		return 0;

	/* Process each match alternative separately until a match is found */
	while ((token = str_token(values, ";", &context))) {
		if (tls_match_suffix_helper(cert, token, full)) {
			ret = 1;
			break;
		}
	}

	os_free(values);
	return ret;
}