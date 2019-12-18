#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; struct TYPE_8__* next; } ;
typedef  TYPE_1__ ucl_object_t ;
struct ucl_schema_error {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ UCL_INT ; 
 int /*<<< orphan*/  UCL_SCHEMA_CONSTRAINT ; 
 TYPE_1__* ucl_object_lookup (TYPE_1__ const*,char*) ; 
 scalar_t__ ucl_object_toint (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_schema_create_error (struct ucl_schema_error*,int /*<<< orphan*/ ,TYPE_1__ const*,char*,long) ; 

__attribute__((used)) static bool
ucl_schema_validate_values (const ucl_object_t *schema, const ucl_object_t *obj,
		struct ucl_schema_error *err)
{
	const ucl_object_t *elt, *cur;
	int64_t constraint, i;

	elt = ucl_object_lookup (schema, "maxValues");
	if (elt != NULL && elt->type == UCL_INT) {
		constraint = ucl_object_toint (elt);
		cur = obj;
		i = 0;
		while (cur) {
			if (i > constraint) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
					"object has more values than defined: %ld",
					(long int)constraint);
				return false;
			}
			i ++;
			cur = cur->next;
		}
	}
	elt = ucl_object_lookup (schema, "minValues");
	if (elt != NULL && elt->type == UCL_INT) {
		constraint = ucl_object_toint (elt);
		cur = obj;
		i = 0;
		while (cur) {
			if (i >= constraint) {
				break;
			}
			i ++;
			cur = cur->next;
		}
		if (i < constraint) {
			ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
					"object has less values than defined: %ld",
					(long int)constraint);
			return false;
		}
	}

	return true;
}