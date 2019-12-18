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
typedef  int /*<<< orphan*/  Name ;

/* Variables and functions */
 int _hx509_Name_to_string (int /*<<< orphan*/ *,char**) ; 
 int decode_Name (void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_Name (int /*<<< orphan*/ *) ; 

int
hx509_unparse_der_name(const void *data, size_t length, char **str)
{
    Name name;
    int ret;

    *str = NULL;

    ret = decode_Name(data, length, &name, NULL);
    if (ret)
	return ret;
    ret = _hx509_Name_to_string(&name, str);
    free_Name(&name);
    return ret;
}