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
struct tls_connection {int /*<<< orphan*/ * check_cert_subject; int /*<<< orphan*/ * domain_match; int /*<<< orphan*/ * suffix_match; int /*<<< orphan*/ * altsubject_match; int /*<<< orphan*/ * subject_match; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 void* os_strdup (char const*) ; 

__attribute__((used)) static int tls_connection_set_subject_match(struct tls_connection *conn,
					    const char *subject_match,
					    const char *altsubject_match,
					    const char *suffix_match,
					    const char *domain_match,
					    const char *check_cert_subject)
{
	os_free(conn->subject_match);
	conn->subject_match = NULL;
	if (subject_match) {
		conn->subject_match = os_strdup(subject_match);
		if (conn->subject_match == NULL)
			return -1;
	}

	os_free(conn->altsubject_match);
	conn->altsubject_match = NULL;
	if (altsubject_match) {
		conn->altsubject_match = os_strdup(altsubject_match);
		if (conn->altsubject_match == NULL)
			return -1;
	}

	os_free(conn->suffix_match);
	conn->suffix_match = NULL;
	if (suffix_match) {
		conn->suffix_match = os_strdup(suffix_match);
		if (conn->suffix_match == NULL)
			return -1;
	}

	os_free(conn->domain_match);
	conn->domain_match = NULL;
	if (domain_match) {
		conn->domain_match = os_strdup(domain_match);
		if (conn->domain_match == NULL)
			return -1;
	}

	os_free(conn->check_cert_subject);
	conn->check_cert_subject = NULL;
	if (check_cert_subject) {
		conn->check_cert_subject = os_strdup(check_cert_subject);
		if (!conn->check_cert_subject)
			return -1;
	}

	return 0;
}