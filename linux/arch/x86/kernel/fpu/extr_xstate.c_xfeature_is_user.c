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

/* Variables and functions */
 int /*<<< orphan*/  xfeature_is_supervisor (int) ; 

__attribute__((used)) static int xfeature_is_user(int xfeature_nr)
{
	return !xfeature_is_supervisor(xfeature_nr);
}