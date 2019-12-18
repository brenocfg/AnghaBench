#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct roff_node {int type; TYPE_3__* norm; TYPE_1__* parent; } ;
struct TYPE_5__ {int type; int count; int /*<<< orphan*/  comp; } ;
struct TYPE_6__ {TYPE_2__ Bl; } ;
struct TYPE_4__ {struct roff_node* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESC_FON ; 
#define  LIST_bullet 141 
#define  LIST_column 140 
#define  LIST_dash 139 
#define  LIST_diag 138 
#define  LIST_enum 137 
#define  LIST_hang 136 
#define  LIST_hyphen 135 
#define  LIST_inset 134 
#define  LIST_item 133 
#define  LIST_ohang 132 
#define  LIST_tag 131 
 int /*<<< orphan*/  MD_br ; 
 int /*<<< orphan*/  MD_nl ; 
 int /*<<< orphan*/  MD_nonl ; 
 int /*<<< orphan*/  MD_sp ; 
 int /*<<< orphan*/  MD_spc ; 
#define  ROFFT_BLOCK 130 
#define  ROFFT_BODY 129 
#define  ROFFT_HEAD 128 
 int /*<<< orphan*/  code_blocks ; 
 int /*<<< orphan*/  escflags ; 
 int /*<<< orphan*/  list_blocks ; 
 int /*<<< orphan*/  md_pre_D1 (struct roff_node*) ; 
 int /*<<< orphan*/  md_preword () ; 
 int /*<<< orphan*/  md_rawword (char*) ; 
 int /*<<< orphan*/  md_stack (char) ; 
 int /*<<< orphan*/  outcount ; 
 int /*<<< orphan*/  outflags ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  quote_blocks ; 

__attribute__((used)) static int
md_pre_It(struct roff_node *n)
{
	struct roff_node	*bln;

	switch (n->type) {
	case ROFFT_BLOCK:
		return 1;

	case ROFFT_HEAD:
		bln = n->parent->parent;
		if (bln->norm->Bl.comp == 0 &&
		    bln->norm->Bl.type != LIST_column)
			outflags |= MD_sp;
		outflags |= MD_nl;

		switch (bln->norm->Bl.type) {
		case LIST_item:
			outflags |= MD_br;
			return 0;
		case LIST_inset:
		case LIST_diag:
		case LIST_ohang:
			outflags |= MD_br;
			return 1;
		case LIST_tag:
		case LIST_hang:
			outflags |= MD_sp;
			return 1;
		case LIST_bullet:
			md_rawword("*\t");
			break;
		case LIST_dash:
		case LIST_hyphen:
			md_rawword("-\t");
			break;
		case LIST_enum:
			md_preword();
			if (bln->norm->Bl.count < 99)
				bln->norm->Bl.count++;
			printf("%d.\t", bln->norm->Bl.count);
			escflags &= ~ESC_FON;
			break;
		case LIST_column:
			outflags |= MD_br;
			return 0;
		default:
			return 0;
		}
		outflags &= ~MD_spc;
		outflags |= MD_nonl;
		outcount = 0;
		md_stack('\t');
		if (code_blocks || quote_blocks)
			list_blocks++;
		return 0;

	case ROFFT_BODY:
		bln = n->parent->parent;
		switch (bln->norm->Bl.type) {
		case LIST_ohang:
			outflags |= MD_br;
			break;
		case LIST_tag:
		case LIST_hang:
			md_pre_D1(n);
			break;
		default:
			break;
		}
		return 1;

	default:
		return 0;
	}
}