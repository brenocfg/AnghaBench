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
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_4__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ret_data_xdr (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
ret_string_xdr(krb5_storage *sp, char **str)
{
    krb5_data c;
    *str = NULL;
    CHECK(ret_data_xdr(sp, &c));
    if (c.length) {
	*str = malloc(c.length + 1);
	INSIST(*str != NULL);
	memcpy(*str, c.data, c.length);
	(*str)[c.length] = '\0';
    }
    krb5_data_free(&c);
    return 0;
}