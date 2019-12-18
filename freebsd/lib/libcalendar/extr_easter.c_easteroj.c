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
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int /*<<< orphan*/  easterodn (int) ; 
 int /*<<< orphan*/ * jdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

date   *
easteroj(int y, date * dt)
{

	return (jdate(easterodn(y), dt));
}