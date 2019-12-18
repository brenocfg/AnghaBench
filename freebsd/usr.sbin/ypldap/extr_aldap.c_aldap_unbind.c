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
struct aldap {int msgid; int /*<<< orphan*/  err; int /*<<< orphan*/  ber; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALDAP_ERR_OPERATION_FAILED ; 
 int /*<<< orphan*/  BER_CLASS_APP ; 
 int /*<<< orphan*/  LDAP_DEBUG (char*,struct ber_element*) ; 
 int /*<<< orphan*/  LDAP_REQ_UNBIND_30 ; 
 struct ber_element* ber_add_sequence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ber_free_elements (struct ber_element*) ; 
 struct ber_element* ber_printf_elements (struct ber_element*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ber_write_elements (int /*<<< orphan*/ *,struct ber_element*) ; 

int
aldap_unbind(struct aldap *ldap)
{
	struct ber_element *root = NULL, *elm;
	int error;

	if ((root = ber_add_sequence(NULL)) == NULL)
		goto fail;
	elm = ber_printf_elements(root, "d{t", ++ldap->msgid, BER_CLASS_APP,
	    LDAP_REQ_UNBIND_30);
	if (elm == NULL)
		goto fail;

	LDAP_DEBUG("aldap_unbind", root);

	error = ber_write_elements(&ldap->ber, root);
	ber_free_elements(root);
	root = NULL;
	if (error == -1)
		goto fail;

	return (ldap->msgid);
fail:
	if (root != NULL)
		ber_free_elements(root);

	ldap->err = ALDAP_ERR_OPERATION_FAILED;

	return (-1);
}