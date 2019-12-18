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
 int cgread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  dumpfreespacecg (int) ; 
 int /*<<< orphan*/  ufserr (char const*) ; 

__attribute__((used)) static int
dumpfreespace(const char *name, int fflag)
{
	int i;

	while ((i = cgread(&disk)) != 0) {
		if (i == -1)
			goto err;
		dumpfreespacecg(fflag);
	}
	return (0);
err:
	ufserr(name);
	return (1);
}