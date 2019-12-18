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
struct eventtimer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  impl ; 
 int /*<<< orphan*/  tick_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tickincrement ; 

__attribute__((used)) static int
tick_et_stop(struct eventtimer *et)
{

	PCPU_SET(tickincrement, 0);
	tick_stop(PCPU_GET(impl));
	return (0);
}