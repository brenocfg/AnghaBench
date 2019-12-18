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
typedef  scalar_t__ uintmax_t ;
typedef  int /*<<< orphan*/  db_strategy_t ;
typedef  unsigned int db_expr_t ;
typedef  unsigned int db_addr_t ;
typedef  int /*<<< orphan*/  c_db_sym_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_DB_SYM_NULL ; 
 int /*<<< orphan*/  X_db_search_symbol (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/ * db_last_symtab ; 
 int db_nsymtab ; 
 int /*<<< orphan*/ * db_symtabs ; 

c_db_sym_t
db_search_symbol(db_addr_t val, db_strategy_t strategy, db_expr_t *offp)
{
	unsigned int	diff;
	size_t		newdiff;
	int		i;
	c_db_sym_t	ret = C_DB_SYM_NULL, sym;

	newdiff = diff = val;
	for (i = 0; i < db_nsymtab; i++) {
	    sym = X_db_search_symbol(&db_symtabs[i], val, strategy, &newdiff);
	    if ((uintmax_t)newdiff < (uintmax_t)diff) {
		db_last_symtab = &db_symtabs[i];
		diff = newdiff;
		ret = sym;
	    }
	}
	*offp = diff;
	return ret;
}