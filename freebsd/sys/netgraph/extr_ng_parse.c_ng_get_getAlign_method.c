#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ng_parse_type {int /*<<< orphan*/ * getAlign; struct ng_parse_type* supertype; } ;
typedef  int /*<<< orphan*/  ng_getAlign_t ;

/* Variables and functions */

__attribute__((used)) static ng_getAlign_t *
ng_get_getAlign_method(const struct ng_parse_type *t)
{
	while (t != NULL && t->getAlign == NULL)
		t = t->supertype;
	return (t ? t->getAlign : NULL);
}