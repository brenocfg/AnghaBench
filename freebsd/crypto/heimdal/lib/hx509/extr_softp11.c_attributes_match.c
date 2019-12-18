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
struct st_object {int num_attributes; TYPE_2__* attrs; } ;
struct TYPE_7__ {scalar_t__ ulValueLen; int /*<<< orphan*/  type; int /*<<< orphan*/  pValue; } ;
struct TYPE_5__ {scalar_t__ ulValueLen; int /*<<< orphan*/  pValue; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ attribute; } ;
typedef  size_t CK_ULONG ;
typedef  TYPE_3__ CK_ATTRIBUTE ;

/* Variables and functions */
 scalar_t__ OBJECT_ID (struct st_object const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  st_logf (char*,...) ; 

__attribute__((used)) static int
attributes_match(const struct st_object *obj,
		 const CK_ATTRIBUTE *attributes,
		 CK_ULONG num_attributes)
{
    CK_ULONG i;
    int j;

    st_logf("attributes_match: %ld\n", (unsigned long)OBJECT_ID(obj));

    for (i = 0; i < num_attributes; i++) {
	int match = 0;
	for (j = 0; j < obj->num_attributes; j++) {
	    if (attributes[i].type == obj->attrs[j].attribute.type &&
		attributes[i].ulValueLen == obj->attrs[j].attribute.ulValueLen &&
		memcmp(attributes[i].pValue, obj->attrs[j].attribute.pValue,
		       attributes[i].ulValueLen) == 0) {
		match = 1;
		break;
	    }
	}
	if (match == 0) {
	    st_logf("type %d attribute have no match\n", attributes[i].type);
	    return 0;
	}
    }
    st_logf("attribute matches\n");
    return 1;
}