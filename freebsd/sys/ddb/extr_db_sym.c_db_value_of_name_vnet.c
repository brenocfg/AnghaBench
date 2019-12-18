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
typedef  int /*<<< orphan*/  tmp ;
struct vnet {scalar_t__ vnet_data_base; } ;
typedef  scalar_t__ db_expr_t ;
typedef  scalar_t__ c_db_sym_t ;

/* Variables and functions */
 scalar_t__ C_DB_SYM_NULL ; 
 scalar_t__ VNET_START ; 
 scalar_t__ VNET_STOP ; 
 struct vnet* curvnet ; 
 scalar_t__ db_lookup (char*) ; 
 int /*<<< orphan*/  db_symbol_values (scalar_t__,char const**,scalar_t__*) ; 
 struct vnet* db_vnet ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

bool
db_value_of_name_vnet(const char *name, db_expr_t *valuep)
{
#ifdef VIMAGE
	static char     tmp[256];
	db_expr_t	value;
	c_db_sym_t	sym;
	struct vnet	*vnet;

	if (db_vnet != NULL)
		vnet = db_vnet;
	else
		vnet = curvnet;
	snprintf(tmp, sizeof(tmp), "vnet_entry_%s", name);
	sym = db_lookup(tmp);
	if (sym == C_DB_SYM_NULL)
		return (false);
	db_symbol_values(sym, &name, &value);
	if (value < VNET_START || value >= VNET_STOP)
		return (false);
	*valuep = (db_expr_t)((uintptr_t)value + vnet->vnet_data_base);
	return (true);
#else
	return (false);
#endif
}