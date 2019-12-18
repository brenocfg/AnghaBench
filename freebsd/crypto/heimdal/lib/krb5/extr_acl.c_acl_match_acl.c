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
struct acl_field {struct acl_field* next; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_boolean ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acl_match_field (int /*<<< orphan*/ ,char*,struct acl_field*) ; 
 int strsep_copy (char const**,char*,char*,int) ; 

__attribute__((used)) static krb5_boolean
acl_match_acl(krb5_context context,
	      struct acl_field *acl,
	      const char *string)
{
    char buf[256];
    while(strsep_copy(&string, " \t", buf, sizeof(buf)) != -1) {
	if(buf[0] == '\0')
	    continue; /* skip ws */
	if (acl == NULL)
	    return FALSE;
	if(!acl_match_field(context, buf, acl)) {
	    return FALSE;
	}
	acl = acl->next;
    }
    if (acl)
	return FALSE;
    return TRUE;
}