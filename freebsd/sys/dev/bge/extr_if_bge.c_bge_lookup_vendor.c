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
typedef  scalar_t__ uint16_t ;
struct bge_vendor {scalar_t__ v_id; int /*<<< orphan*/ * v_name; } ;

/* Variables and functions */
 struct bge_vendor* bge_vendors ; 

__attribute__((used)) static const struct bge_vendor *
bge_lookup_vendor(uint16_t vid)
{
	const struct bge_vendor *v;

	for (v = bge_vendors; v->v_name != NULL; v++)
		if (v->v_id == vid)
			return (v);

	return (NULL);
}