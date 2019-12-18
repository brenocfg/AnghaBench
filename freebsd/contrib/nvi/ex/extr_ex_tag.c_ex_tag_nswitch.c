#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * frp; } ;
struct TYPE_10__ {int /*<<< orphan*/ * frp; int /*<<< orphan*/  fname; } ;
typedef  TYPE_1__ TAG ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 int FS_ALL ; 
 int FS_POSSIBLE ; 
 int /*<<< orphan*/  FS_SETALT ; 
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_FSWITCH ; 
 int /*<<< orphan*/  SC_SCR_CENTER ; 
 int /*<<< orphan*/  SC_SCR_TOP ; 
 int /*<<< orphan*/ * file_add (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ file_m1 (TYPE_2__*,int,int) ; 

int
ex_tag_nswitch(SCR *sp, TAG *tp, int force)
{
	/* Get a file structure. */
	if (tp->frp == NULL && (tp->frp = file_add(sp, tp->fname)) == NULL)
		return (1);

	/* If not changing files, return, we're done. */
	if (tp->frp == sp->frp)
		return (0);

	/* Check for permission to leave. */
	if (file_m1(sp, force, FS_ALL | FS_POSSIBLE))
		return (1);

	/* Initialize the new file. */
	if (file_init(sp, tp->frp, NULL, FS_SETALT))
		return (1);

	/* Display tags in the center of the screen. */
	F_CLR(sp, SC_SCR_TOP);
	F_SET(sp, SC_SCR_CENTER);

	/* Switch. */
	F_SET(sp, SC_FSWITCH);
	return (0);
}