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
 int /*<<< orphan*/  A_GETCAR ; 
 int auditon (int /*<<< orphan*/ ,char*,size_t) ; 

int
audit_get_car(char *path, size_t sz)
{

	return (auditon(A_GETCAR, path, sz));
}