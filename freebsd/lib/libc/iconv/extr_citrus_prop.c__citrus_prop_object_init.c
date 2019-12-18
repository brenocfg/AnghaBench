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
typedef  int /*<<< orphan*/  _citrus_prop_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  u; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ _citrus_prop_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
_citrus_prop_object_init(_citrus_prop_object_t *obj, _citrus_prop_type_t type)
{

	obj->type = type;
	memset(&obj->u, 0, sizeof(obj->u));
}