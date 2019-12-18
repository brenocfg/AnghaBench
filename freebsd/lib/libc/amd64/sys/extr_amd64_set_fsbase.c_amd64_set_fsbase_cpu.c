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
 int /*<<< orphan*/  wrfsbase (uintptr_t) ; 

__attribute__((used)) static int
amd64_set_fsbase_cpu(void *addr)
{

	wrfsbase((uintptr_t)addr);
	return (0);
}