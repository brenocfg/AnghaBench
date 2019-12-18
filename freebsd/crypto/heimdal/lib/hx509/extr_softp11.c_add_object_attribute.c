#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_object {int num_attributes; struct st_attr* attrs; } ;
struct TYPE_2__ {scalar_t__ ulValueLen; int /*<<< orphan*/ * pValue; int /*<<< orphan*/  type; } ;
struct st_attr {int secret; TYPE_1__ attribute; } ;
typedef  int /*<<< orphan*/  CK_VOID_PTR ;
typedef  scalar_t__ CK_ULONG ;
typedef  int /*<<< orphan*/  CK_RV ;
typedef  int /*<<< orphan*/  CK_ATTRIBUTE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_DEVICE_MEMORY ; 
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct st_attr* realloc (struct st_attr*,int) ; 

__attribute__((used)) static CK_RV
add_object_attribute(struct st_object *o,
		     int secret,
		     CK_ATTRIBUTE_TYPE type,
		     CK_VOID_PTR pValue,
		     CK_ULONG ulValueLen)
{
    struct st_attr *a;
    int i;

    i = o->num_attributes;
    a = realloc(o->attrs, (i + 1) * sizeof(o->attrs[0]));
    if (a == NULL)
	return CKR_DEVICE_MEMORY;
    o->attrs = a;
    o->attrs[i].secret = secret;
    o->attrs[i].attribute.type = type;
    o->attrs[i].attribute.pValue = malloc(ulValueLen);
    if (o->attrs[i].attribute.pValue == NULL && ulValueLen != 0)
	return CKR_DEVICE_MEMORY;
    memcpy(o->attrs[i].attribute.pValue, pValue, ulValueLen);
    o->attrs[i].attribute.ulValueLen = ulValueLen;
    o->num_attributes++;

    return CKR_OK;
}