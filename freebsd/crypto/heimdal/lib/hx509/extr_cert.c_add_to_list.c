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
struct TYPE_3__ {int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ hx509_octet_string_list ;
typedef  int /*<<< orphan*/  heim_octet_string ;

/* Variables and functions */
 int ENOMEM ; 
 int der_copy_octet_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 void* realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
add_to_list(hx509_octet_string_list *list, const heim_octet_string *entry)
{
    void *p;
    int ret;

    p = realloc(list->val, (list->len + 1) * sizeof(list->val[0]));
    if (p == NULL)
	return ENOMEM;
    list->val = p;
    ret = der_copy_octet_string(entry, &list->val[list->len]);
    if (ret)
	return ret;
    list->len++;
    return 0;
}