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
struct clone_defcb {int /*<<< orphan*/ * clone_cb; int /*<<< orphan*/  ifprefix; } ;
typedef  int /*<<< orphan*/  clone_callback_func ;

/* Variables and functions */
 scalar_t__ IFNAMSIZ ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct clone_defcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clone_defcbh ; 
 struct clone_defcb* malloc (int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

void
clone_setdefcallback(const char *ifprefix, clone_callback_func *p)
{
	struct clone_defcb *dcp;

	dcp = malloc(sizeof(*dcp));
	strlcpy(dcp->ifprefix, ifprefix, IFNAMSIZ-1);
	dcp->clone_cb = p;
	SLIST_INSERT_HEAD(&clone_defcbh, dcp, next);
}