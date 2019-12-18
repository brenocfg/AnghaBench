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
typedef  int /*<<< orphan*/  uch ;
struct parse {int dummy; } ;

/* Variables and functions */
 int DUPMAX ; 
 int GETNEXT () ; 
 scalar_t__ MORE () ; 
 scalar_t__ PEEK () ; 
 int /*<<< orphan*/  REG_BADBR ; 
 int /*<<< orphan*/  REQUIRE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int			/* the value */
p_count(struct parse *p)
{
	int count = 0;
	int ndigits = 0;

	while (MORE() && isdigit((uch)PEEK()) && count <= DUPMAX) {
		count = count*10 + (GETNEXT() - '0');
		ndigits++;
	}

	REQUIRE(ndigits > 0 && count <= DUPMAX, REG_BADBR);
	return(count);
}