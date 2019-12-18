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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  progress_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  progress_draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  progress_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
progress_complete(progress_t *prog, uint64_t done)
{
	progress_update(prog, done);
	progress_draw(prog);
	printf("\n");
	return 1;
}