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
struct directory {int /*<<< orphan*/  di_name; struct directory* di_prev; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  STRdirstack ; 
 int /*<<< orphan*/ * Strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/ * adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup ; 
 int /*<<< orphan*/  cleanup_ignore (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ **) ; 
 struct directory dhead ; 
 int /*<<< orphan*/  setq (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shvhed ; 
 int /*<<< orphan*/ ** xmalloc (int) ; 

__attribute__((used)) static void
dgetstack(void)
{
    int i = 0;
    Char **dblk, **dbp;
    struct directory *dn;

    if (adrof(STRdirstack) == NULL) 
    	return;

    for (dn = dhead.di_prev; dn != &dhead; dn = dn->di_prev, i++)
	continue;
    dbp = dblk = xmalloc((i + 1) * sizeof(Char *));
    for (dn = dhead.di_prev; dn != &dhead; dn = dn->di_prev, dbp++)
	 *dbp = Strsave(dn->di_name);
    *dbp = NULL;
    cleanup_push(dblk, blk_cleanup);
    setq(STRdirstack, dblk, &shvhed, VAR_READWRITE);
    cleanup_ignore(dblk);
    cleanup_until(dblk);
}