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
struct TYPE_3__ {size_t len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ hx509_octet_string_list ;

/* Variables and functions */
 int /*<<< orphan*/  der_free_octet_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
hx509_free_octet_string_list(hx509_octet_string_list *list)
{
    size_t i;
    for (i = 0; i < list->len; i++)
	der_free_octet_string(&list->val[i]);
    free(list->val);
    list->val = NULL;
    list->len = 0;
}