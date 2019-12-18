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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,scalar_t__) ; 
 scalar_t__ initcount ; 
 scalar_t__ mutex_file ; 

void
ipf_mutex_clean()
{
	if (initcount != 0) {
		if (mutex_file)
			fprintf(mutex_file, "initcount %d\n", initcount);
		abort();
	}
}