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
struct parse {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EATTWO (char,char) ; 
 char GETNEXT () ; 
 int /*<<< orphan*/  MORE () ; 
 int /*<<< orphan*/  REG_EBRACK ; 
 int /*<<< orphan*/  REG_ECOLLATE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char p_b_coll_elem (struct parse*,char) ; 

__attribute__((used)) static char			/* value of symbol */
p_b_symbol(struct parse *p)
{
	char value;

	REQUIRE(MORE(), REG_EBRACK);
	if (!EATTWO('[', '.'))
		return(GETNEXT());

	/* collating symbol */
	value = p_b_coll_elem(p, '.');
	REQUIRE(EATTWO('.', ']'), REG_ECOLLATE);
	return(value);
}