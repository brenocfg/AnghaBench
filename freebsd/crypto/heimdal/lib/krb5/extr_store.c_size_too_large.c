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
struct TYPE_3__ {size_t max_alloc; } ;
typedef  TYPE_1__ krb5_storage ;
typedef  int /*<<< orphan*/  krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  HEIM_ERR_TOO_BIG ; 

__attribute__((used)) static krb5_error_code
size_too_large(krb5_storage *sp, size_t size)
{
    if (sp->max_alloc && sp->max_alloc < size)
	return HEIM_ERR_TOO_BIG;
    return 0;
}