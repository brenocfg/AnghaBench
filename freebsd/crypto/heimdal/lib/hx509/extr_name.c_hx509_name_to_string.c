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
typedef  TYPE_1__* hx509_name ;
struct TYPE_3__ {int /*<<< orphan*/  der_name; } ;

/* Variables and functions */
 int _hx509_Name_to_string (int /*<<< orphan*/ *,char**) ; 

int
hx509_name_to_string(const hx509_name name, char **str)
{
    return _hx509_Name_to_string(&name->der_name, str);
}