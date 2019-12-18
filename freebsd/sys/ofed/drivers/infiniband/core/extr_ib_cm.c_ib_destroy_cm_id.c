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
struct ib_cm_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cm_destroy_id (struct ib_cm_id*,int /*<<< orphan*/ ) ; 

void ib_destroy_cm_id(struct ib_cm_id *cm_id)
{
	cm_destroy_id(cm_id, 0);
}