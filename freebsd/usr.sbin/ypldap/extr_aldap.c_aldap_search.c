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
struct ber_element {int dummy; } ;
struct aldap_page_control {int dummy; } ;
struct aldap {int msgid; void* err; int /*<<< orphan*/  ber; } ;
typedef  enum scope { ____Placeholder_scope } scope ;

/* Variables and functions */
 void* ALDAP_ERR_OPERATION_FAILED ; 
 void* ALDAP_ERR_PARSER_ERROR ; 
 int /*<<< orphan*/  BER_CLASS_APP ; 
 int /*<<< orphan*/  LDAP_DEBUG (char*,struct ber_element*) ; 
 scalar_t__ LDAP_DEREF_NEVER ; 
 scalar_t__ LDAP_REQ_SEARCH ; 
 int /*<<< orphan*/  aldap_create_page_control (struct ber_element*,int,struct aldap_page_control*) ; 
 struct ber_element* ber_add_sequence (struct ber_element*) ; 
 struct ber_element* ber_add_string (struct ber_element*,char*) ; 
 int /*<<< orphan*/  ber_free_elements (struct ber_element*) ; 
 struct ber_element* ber_printf_elements (struct ber_element*,char*,...) ; 
 int ber_write_elements (int /*<<< orphan*/ *,struct ber_element*) ; 
 struct ber_element* ldap_parse_search_filter (struct ber_element*,char*) ; 

int
aldap_search(struct aldap *ldap, char *basedn, enum scope scope, char *filter,
    char **attrs, int typesonly, int sizelimit, int timelimit,
    struct aldap_page_control *page)
{
	struct ber_element *root = NULL, *ber, *c;
	int i, error;

	if ((root = ber_add_sequence(NULL)) == NULL)
		goto fail;

	ber = ber_printf_elements(root, "d{t", ++ldap->msgid, BER_CLASS_APP,
	    (unsigned long) LDAP_REQ_SEARCH);
	if (ber == NULL) {
		ldap->err = ALDAP_ERR_OPERATION_FAILED;
		goto fail;
	}

	c = ber;	
	ber = ber_printf_elements(ber, "sEEddb", basedn, (long long)scope,
	                         (long long)LDAP_DEREF_NEVER, sizelimit, 
				 timelimit, typesonly);
	if (ber == NULL) {
		ldap->err = ALDAP_ERR_OPERATION_FAILED;
		goto fail;
	}

	if ((ber = ldap_parse_search_filter(ber, filter)) == NULL) {
		ldap->err = ALDAP_ERR_PARSER_ERROR;
		goto fail;
	}

	if ((ber = ber_add_sequence(ber)) == NULL)
		goto fail;
	if (attrs != NULL)
		for (i = 0; attrs[i] != NULL; i++) {
			if ((ber = ber_add_string(ber, attrs[i])) == NULL)
				goto fail;
		}

	aldap_create_page_control(c, 100, page);

	LDAP_DEBUG("aldap_search", root);

	error = ber_write_elements(&ldap->ber, root);
	ber_free_elements(root);
	root = NULL;
	if (error == -1) {
		ldap->err = ALDAP_ERR_OPERATION_FAILED;
		goto fail;
	}

	return (ldap->msgid);

fail:
	if (root != NULL)
		ber_free_elements(root);

	return (-1);
}