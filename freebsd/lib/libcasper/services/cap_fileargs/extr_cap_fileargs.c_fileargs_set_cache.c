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
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {int /*<<< orphan*/ * fa_cache; } ;
typedef  TYPE_1__ fileargs_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fileargs_set_cache(fileargs_t *fa, nvlist_t *nvl)
{

	nvlist_destroy(fa->fa_cache);
	fa->fa_cache = nvl;
}