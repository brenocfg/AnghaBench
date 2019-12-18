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
 int /*<<< orphan*/  MD_Bk ; 
#define  ROFFT_BLOCK 130 
#define  ROFFT_ELEM 129 
#define  ROFFT_HEAD 128 
 int /*<<< orphan*/  md_pre_raw (struct roff_node*) ; 
 int /*<<< orphan*/  md_pre_syn (struct roff_node*) ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static int
md_pre_Nm(struct roff_node *n)
{
	switch (n->type) {
	case ROFFT_BLOCK:
		outflags |= MD_Bk;
		md_pre_syn(n);
		break;
	case ROFFT_HEAD:
	case ROFFT_ELEM:
		md_pre_raw(n);
		break;
	default:
		break;
	}
	return 1;
}