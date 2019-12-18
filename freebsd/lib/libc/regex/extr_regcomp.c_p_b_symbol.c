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
typedef  int /*<<< orphan*/  wint_t ;
struct parse {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EATTWO (char,char) ; 
 int /*<<< orphan*/  MORE () ; 
 int /*<<< orphan*/  REG_EBRACK ; 
 int /*<<< orphan*/  REG_ECOLLATE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WGETNEXT () ; 
 int /*<<< orphan*/  p_b_coll_elem (struct parse*,char) ; 

__attribute__((used)) static wint_t			/* value of symbol */
p_b_symbol(struct parse *p)
{
	wint_t value;

	(void)REQUIRE(MORE(), REG_EBRACK);
	if (!EATTWO('[', '.'))
		return(WGETNEXT());

	/* collating symbol */
	value = p_b_coll_elem(p, '.');
	(void)REQUIRE(EATTWO('.', ']'), REG_ECOLLATE);
	return(value);
}