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
struct targbh_cmd_desc {struct targbh_cmd_desc* backing_store; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SCSIBH ; 
 int /*<<< orphan*/  free (struct targbh_cmd_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
targbhfreedescr(struct targbh_cmd_desc *descr)
{
	free(descr->backing_store, M_SCSIBH);
	free(descr, M_SCSIBH);
}