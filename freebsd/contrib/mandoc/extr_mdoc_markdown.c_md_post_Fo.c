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
struct roff_node {int type; int /*<<< orphan*/ * child; } ;

/* Variables and functions */
#define  ROFFT_BODY 129 
#define  ROFFT_HEAD 128 
 int /*<<< orphan*/  md_post_Fn (struct roff_node*) ; 
 int /*<<< orphan*/  md_post_raw (struct roff_node*) ; 

__attribute__((used)) static void
md_post_Fo(struct roff_node *n)
{
	switch (n->type) {
	case ROFFT_HEAD:
		if (n->child != NULL)
			md_post_raw(n);
		break;
	case ROFFT_BODY:
		md_post_Fn(n);
		break;
	default:
		break;
	}
}