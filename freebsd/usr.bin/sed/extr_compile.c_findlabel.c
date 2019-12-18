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
struct s_command {int /*<<< orphan*/  t; } ;
struct labhash {int lh_hash; int lh_ref; struct s_command* lh_cmd; struct labhash* lh_next; } ;

/* Variables and functions */
 int LHMASK ; 
 struct labhash** labels ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct s_command *
findlabel(char *name)
{
	struct labhash *lh;
	u_char *p;
	u_int h, c;

	for (h = 0, p = (u_char *)name; (c = *p) != 0; p++)
		h = (h << 5) + h + c;
	for (lh = labels[h & LHMASK]; lh != NULL; lh = lh->lh_next) {
		if (lh->lh_hash == h && strcmp(name, lh->lh_cmd->t) == 0) {
			lh->lh_ref = 1;
			return (lh->lh_cmd);
		}
	}
	return (NULL);
}