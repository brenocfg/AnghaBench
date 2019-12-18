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
struct ggd_export {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct ggd_export* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_next ; 
 int /*<<< orphan*/  exports ; 
 int /*<<< orphan*/  free (struct ggd_export*) ; 

__attribute__((used)) static void
exports_clear(void)
{
	struct ggd_export *ex;

	while (!SLIST_EMPTY(&exports)) {
		ex = SLIST_FIRST(&exports);
		SLIST_REMOVE_HEAD(&exports, e_next);
		free(ex);
	}
}