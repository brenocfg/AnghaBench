#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_3__* hx509_ca_tbs ;
typedef  int /*<<< orphan*/  heim_oid ;
typedef  int /*<<< orphan*/  heim_octet_string ;
typedef  int /*<<< orphan*/  gn ;
struct TYPE_8__ {int /*<<< orphan*/  value; int /*<<< orphan*/  type_id; } ;
struct TYPE_9__ {TYPE_1__ otherName; } ;
struct TYPE_11__ {TYPE_2__ u; int /*<<< orphan*/  element; } ;
struct TYPE_10__ {int /*<<< orphan*/  san; } ;
typedef  TYPE_4__ GeneralName ;

/* Variables and functions */
 int add_GeneralNames (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  choice_GeneralName_otherName ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

int
hx509_ca_tbs_add_san_otherName(hx509_context context,
			       hx509_ca_tbs tbs,
			       const heim_oid *oid,
			       const heim_octet_string *os)
{
    GeneralName gn;

    memset(&gn, 0, sizeof(gn));
    gn.element = choice_GeneralName_otherName;
    gn.u.otherName.type_id = *oid;
    gn.u.otherName.value = *os;

    return add_GeneralNames(&tbs->san, &gn);
}