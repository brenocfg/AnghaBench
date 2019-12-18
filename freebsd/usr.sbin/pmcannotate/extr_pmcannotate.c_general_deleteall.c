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
struct entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_iter ; 
 int /*<<< orphan*/  mainlst ; 

__attribute__((used)) static void
general_deleteall(void)
{
	struct entry *obj;

	while (TAILQ_EMPTY(&mainlst) == 0) {
		obj = TAILQ_FIRST(&mainlst);
		TAILQ_REMOVE(&mainlst, obj, en_iter);
	}
}