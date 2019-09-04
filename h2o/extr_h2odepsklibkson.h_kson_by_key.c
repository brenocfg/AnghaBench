#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__** child; } ;
struct TYPE_7__ {scalar_t__ key; TYPE_1__ v; scalar_t__ n; } ;
typedef  TYPE_2__ kson_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  kson_is_internal (TYPE_2__ const*) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static inline const kson_node_t *kson_by_key(const kson_node_t *p, const char *key)
{
	long i;
	if (!kson_is_internal(p)) return 0;
	for (i = 0; i < (long)p->n; ++i) {
		const kson_node_t *q = p->v.child[i];
		if (q->key && strcmp(q->key, key) == 0)
			return q;
	}
	return 0;
}