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
 int EX_OK ; 
 int /*<<< orphan*/  get_statistics (char*) ; 

int
main(int argc, char **argv)
{
	get_statistics((argc > 1) ? argv[1] : "iwi0");

	return EX_OK;
}