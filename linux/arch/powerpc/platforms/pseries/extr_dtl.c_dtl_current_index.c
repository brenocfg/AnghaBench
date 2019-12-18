#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct dtl {int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dtl_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__ lppaca_of (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 dtl_current_index(struct dtl *dtl)
{
	return be64_to_cpu(lppaca_of(dtl->cpu).dtl_idx);
}