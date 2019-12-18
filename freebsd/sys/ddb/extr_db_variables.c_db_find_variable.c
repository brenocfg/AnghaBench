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
struct db_variable {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct db_variable* db_eregs ; 
 int /*<<< orphan*/  db_error (char*) ; 
 struct db_variable* db_evars ; 
 int db_read_token () ; 
 struct db_variable* db_regs ; 
 int /*<<< orphan*/  db_tok_string ; 
 struct db_variable* db_vars ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tIDENT ; 

__attribute__((used)) static int
db_find_variable(struct db_variable **varp)
{
	struct db_variable *vp;
	int t;

	t = db_read_token();
	if (t == tIDENT) {
		for (vp = db_vars; vp < db_evars; vp++) {
			if (!strcmp(db_tok_string, vp->name)) {
				*varp = vp;
				return (1);
			}
		}
		for (vp = db_regs; vp < db_eregs; vp++) {
			if (!strcmp(db_tok_string, vp->name)) {
				*varp = vp;
				return (1);
			}
		}
	}
	db_error("Unknown variable\n");
	return (0);
}