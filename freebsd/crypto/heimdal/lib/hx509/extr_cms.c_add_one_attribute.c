#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ heim_octet_string ;
struct TYPE_11__ {TYPE_1__* val; } ;
struct TYPE_10__ {TYPE_7__ value; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_SEQ (TYPE_7__*,int) ; 
 int ENOMEM ; 
 int der_copy_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 void* realloc (TYPE_3__*,int) ; 

__attribute__((used)) static int
add_one_attribute(Attribute **attr,
		  unsigned int *len,
		  const heim_oid *oid,
		  heim_octet_string *data)
{
    void *d;
    int ret;

    d = realloc(*attr, sizeof((*attr)[0]) * (*len + 1));
    if (d == NULL)
	return ENOMEM;
    (*attr) = d;

    ret = der_copy_oid(oid, &(*attr)[*len].type);
    if (ret)
	return ret;

    ALLOC_SEQ(&(*attr)[*len].value, 1);
    if ((*attr)[*len].value.val == NULL) {
	der_free_oid(&(*attr)[*len].type);
	return ENOMEM;
    }

    (*attr)[*len].value.val[0].data = data->data;
    (*attr)[*len].value.val[0].length = data->length;

    *len += 1;

    return 0;
}