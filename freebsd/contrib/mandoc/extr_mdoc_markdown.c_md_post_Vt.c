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
struct roff_node {int type; } ;

/* Variables and functions */
#define  ROFFT_BODY 129 
#define  ROFFT_ELEM 128 
 int /*<<< orphan*/  md_post_raw (struct roff_node*) ; 

__attribute__((used)) static void
md_post_Vt(struct roff_node *n)
{
	switch (n->type) {
	case ROFFT_BODY:
	case ROFFT_ELEM:
		md_post_raw(n);
		break;
	default:
		break;
	}
}