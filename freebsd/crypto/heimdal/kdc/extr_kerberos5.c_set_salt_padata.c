#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int len; TYPE_1__* val; } ;
struct TYPE_8__ {int /*<<< orphan*/  salt; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  padata_value; int /*<<< orphan*/  padata_type; } ;
typedef  TYPE_2__ Salt ;
typedef  TYPE_3__ METHOD_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  der_copy_octet_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realloc_method_data (TYPE_3__*) ; 

__attribute__((used)) static void
set_salt_padata(METHOD_DATA *md, Salt *salt)
{
    if (salt) {
       realloc_method_data(md);
       md->val[md->len - 1].padata_type = salt->type;
       der_copy_octet_string(&salt->salt,
                             &md->val[md->len - 1].padata_value);
    }
}