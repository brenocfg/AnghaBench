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
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  classes ; 
 int /*<<< orphan*/  kld_sx ; 
 int /*<<< orphan*/  linker_files ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
linker_init(void *arg)
{

	sx_init(&kld_sx, "kernel linker");
	TAILQ_INIT(&classes);
	TAILQ_INIT(&linker_files);
}