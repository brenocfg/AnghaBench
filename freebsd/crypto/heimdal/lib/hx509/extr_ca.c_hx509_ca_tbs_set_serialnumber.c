#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_2__* hx509_ca_tbs ;
typedef  int /*<<< orphan*/  heim_integer ;
struct TYPE_4__ {int serial; } ;
struct TYPE_5__ {TYPE_1__ flags; int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int der_copy_heim_integer (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_heim_integer (int /*<<< orphan*/ *) ; 

int
hx509_ca_tbs_set_serialnumber(hx509_context context,
			      hx509_ca_tbs tbs,
			      const heim_integer *serialNumber)
{
    int ret;
    der_free_heim_integer(&tbs->serial);
    ret = der_copy_heim_integer(serialNumber, &tbs->serial);
    tbs->flags.serial = !ret;
    return ret;
}