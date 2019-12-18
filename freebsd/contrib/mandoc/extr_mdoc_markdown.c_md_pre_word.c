#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct roff_node {int /*<<< orphan*/  tok; } ;
struct TYPE_2__ {char* prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_spc ; 
 TYPE_1__* md_act (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_word (char const*) ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static int
md_pre_word(struct roff_node *n)
{
	const char	*prefix;

	if ((prefix = md_act(n->tok)->prefix) != NULL) {
		md_word(prefix);
		outflags &= ~MD_spc;
	}
	return 1;
}