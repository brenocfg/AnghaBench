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
struct roff_node {int type; int /*<<< orphan*/  tok; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDOC_Sh ; 
 int MD_An_nosplit ; 
 int MD_An_split ; 
 int MD_sp ; 
#define  ROFFT_BLOCK 130 
#define  ROFFT_BODY 129 
#define  ROFFT_HEAD 128 
 int /*<<< orphan*/  SEC_AUTHORS ; 
 int /*<<< orphan*/  md_rawword (char*) ; 
 int outflags ; 

__attribute__((used)) static int
md_pre_Sh(struct roff_node *n)
{
	switch (n->type) {
	case ROFFT_BLOCK:
		if (n->sec == SEC_AUTHORS)
			outflags &= ~(MD_An_split | MD_An_nosplit);
		break;
	case ROFFT_HEAD:
		outflags |= MD_sp;
		md_rawword(n->tok == MDOC_Sh ? "#" : "##");
		break;
	case ROFFT_BODY:
		outflags |= MD_sp;
		break;
	default:
		break;
	}
	return 1;
}