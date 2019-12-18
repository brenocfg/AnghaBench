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
struct uni {int custat; } ;
typedef  enum cu_stat { ____Placeholder_cu_stat } cu_stat ;

/* Variables and functions */
 int /*<<< orphan*/  cufilt ; 
 int /*<<< orphan*/  uni_undel (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_custat(struct uni *uni, enum cu_stat nstate)
{
	if (uni->custat != nstate) {
		uni->custat = nstate;
		uni_undel(uni, cufilt, NULL);
	}
}