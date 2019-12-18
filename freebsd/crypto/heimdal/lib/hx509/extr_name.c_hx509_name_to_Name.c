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
typedef  int /*<<< orphan*/  Name ;

/* Variables and functions */
 int copy_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
hx509_name_to_Name(const hx509_name from, Name *to)
{
    return copy_Name(&from->der_name, to);
}