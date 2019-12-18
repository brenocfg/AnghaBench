#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  princ ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {int /*<<< orphan*/  principal; } ;
typedef  TYPE_1__ kadm5_principal_ent_rec ;

/* Variables and functions */
 int KADM5_PRINCIPAL ; 
 scalar_t__ kadm5_create_principal (void*,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  kadm5_free_principal_ent (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rand () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static void
add_user (krb5_context context, void *kadm_handle,
	  unsigned nwords, char **words)
{
    kadm5_principal_ent_rec princ;
    char name[64];
    int r1, r2;
    krb5_error_code ret;
    int mask;

    r1 = rand();
    r2 = rand();

    snprintf (name, sizeof(name), "%s%d", words[r1 % nwords], r2 % 1000);

    mask = KADM5_PRINCIPAL;

    memset(&princ, 0, sizeof(princ));
    ret = krb5_parse_name(context, name, &princ.principal);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = kadm5_create_principal (kadm_handle, &princ, mask, name);
    if (ret)
	krb5_err (context, 1, ret, "kadm5_create_principal");
    kadm5_free_principal_ent(kadm_handle, &princ);
    printf ("%s\n", name);
}