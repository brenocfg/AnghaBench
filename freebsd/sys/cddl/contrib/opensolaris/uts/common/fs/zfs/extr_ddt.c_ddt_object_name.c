#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum ddt_type { ____Placeholder_ddt_type } ddt_type ;
typedef  enum ddt_class { ____Placeholder_ddt_class } ddt_class ;
struct TYPE_5__ {size_t ddt_checksum; } ;
typedef  TYPE_1__ ddt_t ;
struct TYPE_7__ {int /*<<< orphan*/  ddt_op_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  ci_name; } ;

/* Variables and functions */
 char* DMU_POOL_DDT ; 
 int /*<<< orphan*/ * ddt_class_name ; 
 TYPE_3__** ddt_ops ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zio_checksum_table ; 

void
ddt_object_name(ddt_t *ddt, enum ddt_type type, enum ddt_class class,
    char *name)
{
	(void) sprintf(name, DMU_POOL_DDT,
	    zio_checksum_table[ddt->ddt_checksum].ci_name,
	    ddt_ops[type]->ddt_op_name, ddt_class_name[class]);
}