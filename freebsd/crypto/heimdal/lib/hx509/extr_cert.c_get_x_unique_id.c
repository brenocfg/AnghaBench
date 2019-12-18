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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_bit_string ;

/* Variables and functions */
 int HX509_EXTENSION_NOT_FOUND ; 
 int der_copy_bit_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*) ; 

__attribute__((used)) static int
get_x_unique_id(hx509_context context, const char *name,
		const heim_bit_string *cert, heim_bit_string *subject)
{
    int ret;

    if (cert == NULL) {
	ret = HX509_EXTENSION_NOT_FOUND;
	hx509_set_error_string(context, 0, ret, "%s unique id doesn't exists", name);
	return ret;
    }
    ret = der_copy_bit_string(cert, subject);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "malloc out of memory", name);
	return ret;
    }
    return 0;
}