#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_name ;
struct TYPE_5__ {int /*<<< orphan*/  der_name; } ;
typedef  int /*<<< orphan*/  Name ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* calloc (int,int) ; 
 int copy_Name (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int
_hx509_name_from_Name(const Name *n, hx509_name *name)
{
    int ret;
    *name = calloc(1, sizeof(**name));
    if (*name == NULL)
	return ENOMEM;
    ret = copy_Name(n, &(*name)->der_name);
    if (ret) {
	free(*name);
	*name = NULL;
    }
    return ret;
}