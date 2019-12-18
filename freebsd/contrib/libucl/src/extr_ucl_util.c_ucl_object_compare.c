#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int type; int len; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct TYPE_19__ {unsigned int n; } ;

/* Variables and functions */
#define  UCL_ARRAY 134 
 int /*<<< orphan*/  UCL_ARRAY_GET (TYPE_2__*,TYPE_1__ const*) ; 
#define  UCL_BOOLEAN 133 
#define  UCL_FLOAT 132 
#define  UCL_INT 131 
#define  UCL_OBJECT 130 
#define  UCL_STRING 129 
#define  UCL_TIME 128 
 TYPE_1__* kv_A (TYPE_2__,unsigned int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ucl_object_iterate (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_object_key (TYPE_1__ const*) ; 
 TYPE_1__* ucl_object_lookup (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int ucl_object_toboolean (TYPE_1__ const*) ; 
 int ucl_object_todouble (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_object_tostring (TYPE_1__ const*) ; 
 TYPE_2__* vec1 ; 
 TYPE_2__* vec2 ; 

int
ucl_object_compare (const ucl_object_t *o1, const ucl_object_t *o2)
{
	const ucl_object_t *it1, *it2;
	ucl_object_iter_t iter = NULL;
	int ret = 0;

	if (o1->type != o2->type) {
		return (o1->type) - (o2->type);
	}

	switch (o1->type) {
	case UCL_STRING:
		if (o1->len == o2->len && o1->len > 0) {
			ret = strcmp (ucl_object_tostring(o1), ucl_object_tostring(o2));
		}
		else {
			ret = o1->len - o2->len;
		}
		break;
	case UCL_FLOAT:
	case UCL_INT:
	case UCL_TIME:
		ret = ucl_object_todouble (o1) - ucl_object_todouble (o2);
		break;
	case UCL_BOOLEAN:
		ret = ucl_object_toboolean (o1) - ucl_object_toboolean (o2);
		break;
	case UCL_ARRAY:
		if (o1->len == o2->len && o1->len > 0) {
			UCL_ARRAY_GET (vec1, o1);
			UCL_ARRAY_GET (vec2, o2);
			unsigned i;

			/* Compare all elements in both arrays */
			for (i = 0; i < vec1->n; i ++) {
				it1 = kv_A (*vec1, i);
				it2 = kv_A (*vec2, i);

				if (it1 == NULL && it2 != NULL) {
					return -1;
				}
				else if (it2 == NULL && it1 != NULL) {
					return 1;
				}
				else if (it1 != NULL && it2 != NULL) {
					ret = ucl_object_compare (it1, it2);
					if (ret != 0) {
						break;
					}
				}
			}
		}
		else {
			ret = o1->len - o2->len;
		}
		break;
	case UCL_OBJECT:
		if (o1->len == o2->len && o1->len > 0) {
			while ((it1 = ucl_object_iterate (o1, &iter, true)) != NULL) {
				it2 = ucl_object_lookup (o2, ucl_object_key (it1));
				if (it2 == NULL) {
					ret = 1;
					break;
				}
				ret = ucl_object_compare (it1, it2);
				if (ret != 0) {
					break;
				}
			}
		}
		else {
			ret = o1->len - o2->len;
		}
		break;
	default:
		ret = 0;
		break;
	}

	return ret;
}