#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  krb5_salt ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_enctype_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_string_to_key_salt_opaque (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int,long,long) ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,struct timeval*) ; 

__attribute__((used)) static void
time_s2k(krb5_context context,
	 krb5_enctype etype,
	 const char *password,
	 krb5_salt salt,
	 int iterations)
{
    struct timeval tv1, tv2;
    krb5_error_code ret;
    krb5_keyblock key;
    krb5_data opaque;
    char *etype_name;
    int i;

    ret = krb5_enctype_to_string(context, etype, &etype_name);
    if (ret)
	krb5_err(context, 1, ret, "krb5_enctype_to_string");

    opaque.data = NULL;
    opaque.length = 0;

    gettimeofday(&tv1, NULL);

    for (i = 0; i < iterations; i++) {
	ret = krb5_string_to_key_salt_opaque(context, etype, password, salt,
					 opaque, &key);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_string_to_key_data_salt_opaque");
	krb5_free_keyblock_contents(context, &key);
    }

    gettimeofday(&tv2, NULL);

    timevalsub(&tv2, &tv1);

    printf("%s string2key %d iterations time: %3ld.%06ld\n",
	   etype_name, iterations, (long)tv2.tv_sec, (long)tv2.tv_usec);
    free(etype_name);

}