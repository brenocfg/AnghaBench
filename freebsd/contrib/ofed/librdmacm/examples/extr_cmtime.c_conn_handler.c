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
struct node {int dummy; } ;

/* Variables and functions */
 size_t STEP_CONNECT ; 
 int /*<<< orphan*/ * completed ; 
 int /*<<< orphan*/  end_perf (struct node*,size_t) ; 

__attribute__((used)) static void conn_handler(struct node *n)
{
	end_perf(n, STEP_CONNECT);
	completed[STEP_CONNECT]++;
}