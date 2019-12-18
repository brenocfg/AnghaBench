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
 int* descriptors ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int ndescriptors ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
descriptor_get(int pos)
{

	if (pos < 0 || pos >= ndescriptors) {
		fprintf(stderr, "invalid descriptor %d\n", pos);
		exit(1);
	}

	return (descriptors[pos]);
}