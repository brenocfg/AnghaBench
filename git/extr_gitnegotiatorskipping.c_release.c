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
struct fetch_negotiator {scalar_t__ data; } ;
struct data {int /*<<< orphan*/  rev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (scalar_t__) ; 
 int /*<<< orphan*/  clear_prio_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release(struct fetch_negotiator *n)
{
	clear_prio_queue(&((struct data *)n->data)->rev_list);
	FREE_AND_NULL(n->data);
}