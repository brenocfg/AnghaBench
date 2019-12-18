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
typedef  int u_int ;
typedef  int u_char ;
struct s_command {scalar_t__ t; } ;
struct labhash {int lh_hash; scalar_t__ lh_ref; struct s_command* lh_cmd; struct labhash* lh_next; } ;

/* Variables and functions */
 int LHMASK ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fname ; 
 struct labhash** labels ; 
 int /*<<< orphan*/  linenum ; 
 struct labhash* malloc (int) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
enterlabel(struct s_command *cp)
{
	struct labhash **lhp, *lh;
	u_char *p;
	u_int h, c;

	for (h = 0, p = (u_char *)cp->t; (c = *p) != 0; p++)
		h = (h << 5) + h + c;
	lhp = &labels[h & LHMASK];
	for (lh = *lhp; lh != NULL; lh = lh->lh_next)
		if (lh->lh_hash == h && strcmp(cp->t, lh->lh_cmd->t) == 0)
			errx(1, "%lu: %s: duplicate label '%s'", linenum, fname, cp->t);
	if ((lh = malloc(sizeof *lh)) == NULL)
		err(1, "malloc");
	lh->lh_next = *lhp;
	lh->lh_hash = h;
	lh->lh_cmd = cp;
	lh->lh_ref = 0;
	*lhp = lh;
}