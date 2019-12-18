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
struct vop_print_args {struct vnode* a_vp; } ;
struct vnode {struct autofs_node* v_data; } ;
struct autofs_node {char* an_name; int an_fileno; int an_cached; int an_wildcards; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 

__attribute__((used)) static int
autofs_print(struct vop_print_args *ap)
{
	struct vnode *vp;
	struct autofs_node *anp;

	vp = ap->a_vp;
	anp = vp->v_data;

	printf("    name \"%s\", fileno %d, cached %d, wildcards %d\n",
	    anp->an_name, anp->an_fileno, anp->an_cached, anp->an_wildcards);

	return (0);
}