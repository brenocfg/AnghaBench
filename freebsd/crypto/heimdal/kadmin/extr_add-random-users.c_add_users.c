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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  KADM5_ADMIN_SERVICE ; 
 int /*<<< orphan*/  add_user (int /*<<< orphan*/ ,void*,unsigned int,char**) ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  kadm5_destroy (void*) ; 
 scalar_t__ kadm5_s_init_with_password_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 unsigned int read_words (char const*,char***) ; 

__attribute__((used)) static void
add_users (const char *filename, unsigned n)
{
    krb5_error_code ret;
    int i;
    void *kadm_handle;
    krb5_context context;
    unsigned nwords;
    char **words;

    ret = krb5_init_context(&context);
    if (ret)
	errx (1, "krb5_init_context failed: %d", ret);
    ret = kadm5_s_init_with_password_ctx(context,
					 KADM5_ADMIN_SERVICE,
					 NULL,
					 KADM5_ADMIN_SERVICE,
					 NULL, 0, 0,
					 &kadm_handle);
    if(ret)
	krb5_err(context, 1, ret, "kadm5_init_with_password");

    nwords = read_words (filename, &words);

    for (i = 0; i < n; ++i)
	add_user (context, kadm_handle, nwords, words);
    kadm5_destroy(kadm_handle);
    krb5_free_context(context);
}