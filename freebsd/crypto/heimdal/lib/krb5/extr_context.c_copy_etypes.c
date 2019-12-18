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
typedef  int /*<<< orphan*/  ret_enctypes ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  scalar_t__ krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static krb5_error_code
copy_etypes (krb5_context context,
	     krb5_enctype *enctypes,
	     krb5_enctype **ret_enctypes)
{
    unsigned int i;

    for (i = 0; enctypes[i]; i++)
	;
    i++;

    *ret_enctypes = malloc(sizeof(ret_enctypes[0]) * i);
    if (*ret_enctypes == NULL) {
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    memcpy(*ret_enctypes, enctypes, sizeof(ret_enctypes[0]) * i);
    return 0;
}