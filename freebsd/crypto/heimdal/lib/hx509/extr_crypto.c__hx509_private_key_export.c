#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_key_format_t ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_octet_string ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int (* export ) (int /*<<< orphan*/ ,TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int HX509_UNIMPLEMENTED_OPERATION ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
_hx509_private_key_export(hx509_context context,
			  const hx509_private_key key,
			  hx509_key_format_t format,
			  heim_octet_string *data)
{
    if (key->ops->export == NULL) {
	hx509_clear_error_string(context);
	return HX509_UNIMPLEMENTED_OPERATION;
    }
    return (*key->ops->export)(context, key, format, data);
}