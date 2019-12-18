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
struct object {int dummy; } ;
struct name_decoration {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECORATE_SHORT_REFS ; 
 int /*<<< orphan*/  load_ref_decorations (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct name_decoration const* lookup_decoration (int /*<<< orphan*/ *,struct object const*) ; 
 int /*<<< orphan*/  name_decoration ; 

const struct name_decoration *get_name_decoration(const struct object *obj)
{
	load_ref_decorations(NULL, DECORATE_SHORT_REFS);
	return lookup_decoration(&name_decoration, obj);
}