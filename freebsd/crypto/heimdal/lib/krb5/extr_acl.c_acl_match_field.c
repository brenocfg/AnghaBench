#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * retv; int /*<<< orphan*/  cstr; } ;
struct acl_field {scalar_t__ type; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int krb5_boolean ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ acl_fnmatch ; 
 scalar_t__ acl_retval ; 
 scalar_t__ acl_string ; 
 int /*<<< orphan*/  fnmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static krb5_boolean
acl_match_field(krb5_context context,
		const char *string,
		struct acl_field *field)
{
    if(field->type == acl_string) {
	return !strcmp(field->u.cstr, string);
    } else if(field->type == acl_fnmatch) {
	return !fnmatch(field->u.cstr, string, 0);
    } else if(field->type == acl_retval) {
	*field->u.retv = strdup(string);
	return TRUE;
    }
    return FALSE;
}