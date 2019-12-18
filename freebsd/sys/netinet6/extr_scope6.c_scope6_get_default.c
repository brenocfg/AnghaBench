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
struct scope6_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCOPE6_LOCK () ; 
 int /*<<< orphan*/  SCOPE6_UNLOCK () ; 
 struct scope6_id V_sid_default ; 

int
scope6_get_default(struct scope6_id *idlist)
{

	SCOPE6_LOCK();
	*idlist = V_sid_default;
	SCOPE6_UNLOCK();

	return (0);
}