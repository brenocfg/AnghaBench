#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_salt ;
struct TYPE_4__ {scalar_t__* key_data_contents; int /*<<< orphan*/ * key_data_length; int /*<<< orphan*/ * key_data_type; } ;
typedef  TYPE_1__ krb5_key_data ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ cmp_salt (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_enctype_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ krb5_salttype_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void
format_keytype(krb5_key_data *k, krb5_salt *def_salt, char *buf, size_t buf_len)
{
    krb5_error_code ret;
    char *s;

    ret = krb5_enctype_to_string (context,
				  k->key_data_type[0],
				  &s);
    if (ret)
	asprintf (&s, "unknown(%d)", k->key_data_type[0]);
    strlcpy(buf, s, buf_len);
    free(s);

    strlcat(buf, "(", buf_len);

    ret = krb5_salttype_to_string (context,
				   k->key_data_type[0],
				   k->key_data_type[1],
				   &s);
    if (ret)
	asprintf (&s, "unknown(%d)", k->key_data_type[1]);
    strlcat(buf, s, buf_len);
    free(s);

    if (cmp_salt(def_salt, k) == 0)
	s = strdup("");
    else if(k->key_data_length[1] == 0)
	s = strdup("()");
    else
	asprintf (&s, "(%.*s)", k->key_data_length[1],
		  (char *)k->key_data_contents[1]);
    strlcat(buf, s, buf_len);
    free(s);

    strlcat(buf, ")", buf_len);
}