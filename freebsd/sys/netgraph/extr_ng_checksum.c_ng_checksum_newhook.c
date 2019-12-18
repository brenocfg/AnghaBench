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
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;
struct TYPE_3__ {void* out; void* in; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_CHECKSUM_HOOK_IN ; 
 int /*<<< orphan*/  NG_CHECKSUM_HOOK_OUT ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_checksum_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (strncmp(name, NG_CHECKSUM_HOOK_IN, strlen(NG_CHECKSUM_HOOK_IN)) == 0) {
		priv->in = hook;
	} else if (strncmp(name, NG_CHECKSUM_HOOK_OUT, strlen(NG_CHECKSUM_HOOK_OUT)) == 0) {
		priv->out = hook;
	} else
		return (EINVAL);

	return (0);
}