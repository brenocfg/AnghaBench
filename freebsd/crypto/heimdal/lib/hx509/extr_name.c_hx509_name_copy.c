#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_6__ {int /*<<< orphan*/  der_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* calloc (int,int) ; 
 int copy_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int
hx509_name_copy(hx509_context context, const hx509_name from, hx509_name *to)
{
    int ret;

    *to = calloc(1, sizeof(**to));
    if (*to == NULL)
	return ENOMEM;
    ret = copy_Name(&from->der_name, &(*to)->der_name);
    if (ret) {
	free(*to);
	*to = NULL;
	return ENOMEM;
    }
    return 0;
}