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
struct ng_type {int (* constructor ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 
 struct ng_type* ng_findtype (char const*) ; 
 int ng_make_node_common (struct ng_type*,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int
ng_make_node(const char *typename, node_p *nodepp)
{
	struct ng_type *type;
	int	error;

	/* Check that the type makes sense */
	if (typename == NULL) {
		TRAP_ERROR();
		return (EINVAL);
	}

	/* Locate the node type. If we fail we return. Do not try to load
	 * module.
	 */
	if ((type = ng_findtype(typename)) == NULL)
		return (ENXIO);

	/*
	 * If we have a constructor, then make the node and
	 * call the constructor to do type specific initialisation.
	 */
	if (type->constructor != NULL) {
		if ((error = ng_make_node_common(type, nodepp)) == 0) {
			if ((error = ((*type->constructor)(*nodepp))) != 0) {
				NG_NODE_UNREF(*nodepp);
			}
		}
	} else {
		/*
		 * Node has no constructor. We cannot ask for one
		 * to be made. It must be brought into existence by
		 * some external agency. The external agency should
		 * call ng_make_node_common() directly to get the
		 * netgraph part initialised.
		 */
		TRAP_ERROR();
		error = EINVAL;
	}
	return (error);
}