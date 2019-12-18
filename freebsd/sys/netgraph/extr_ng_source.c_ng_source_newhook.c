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
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;
struct TYPE_3__ {int /*<<< orphan*/  stats; int /*<<< orphan*/ * output_ifp; void* output; void* input; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SOURCE_HOOK_INPUT ; 
 int /*<<< orphan*/  NG_SOURCE_HOOK_OUTPUT ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_source_newhook(node_p node, hook_p hook, const char *name)
{
	sc_p sc = NG_NODE_PRIVATE(node);

	if (strcmp(name, NG_SOURCE_HOOK_INPUT) == 0) {
		sc->input = hook;
	} else if (strcmp(name, NG_SOURCE_HOOK_OUTPUT) == 0) {
		sc->output = hook;
		sc->output_ifp = NULL;
		bzero(&sc->stats, sizeof(sc->stats));
	} else
		return (EINVAL);

	return (0);
}