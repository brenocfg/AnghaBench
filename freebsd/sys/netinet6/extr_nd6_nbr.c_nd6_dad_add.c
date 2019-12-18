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
struct dadq {int dad_ondadq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DADQ_WLOCK () ; 
 int /*<<< orphan*/  DADQ_WUNLOCK () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct dadq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_dadq ; 
 int /*<<< orphan*/  dad_list ; 

__attribute__((used)) static void
nd6_dad_add(struct dadq *dp)
{

	DADQ_WLOCK();
	TAILQ_INSERT_TAIL(&V_dadq, dp, dad_list);
	dp->dad_ondadq = true;
	DADQ_WUNLOCK();
}