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
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 int /*<<< orphan*/  OVERALL_REF ; 
 int /*<<< orphan*/  REFERRERS ; 
 int /*<<< orphan*/  ht_get_size_datamap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskeyival (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
poverall_refs (GJSON * json, int sp)
{
  pskeyival (json, OVERALL_REF, ht_get_size_datamap (REFERRERS), sp, 0);
}