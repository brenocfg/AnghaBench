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
 int Z_OK ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static __inline void
check_err(int err, const char *func)
{
	if (err != Z_OK) {
		fprintf(stderr, "Compress error in %s: %d\n", func, err);
		exit(0);
	}
}