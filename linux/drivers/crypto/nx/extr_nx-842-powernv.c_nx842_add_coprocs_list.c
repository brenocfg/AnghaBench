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
struct nx842_coproc {int chip_id; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nx842_coprocs ; 

__attribute__((used)) static inline void nx842_add_coprocs_list(struct nx842_coproc *coproc,
					int chipid)
{
	coproc->chip_id = chipid;
	INIT_LIST_HEAD(&coproc->list);
	list_add(&coproc->list, &nx842_coprocs);
}