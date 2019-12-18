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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ ISOPTSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_op ; 
 int /*<<< orphan*/  opttochk ; 
 int /*<<< orphan*/  p_pidobj ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,char**,int) ; 

__attribute__((used)) static int
select_pidobj(uint32_t pid) 
{

	if (ISOPTSET(opttochk, OPT_op)) {
		if (pid != (uint32_t)strtol(p_pidobj, (char **)NULL, 10))
			return (0);
	} 
	return (1);
}