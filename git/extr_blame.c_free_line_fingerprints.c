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
struct fingerprint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_fingerprint (struct fingerprint*) ; 

__attribute__((used)) static void free_line_fingerprints(struct fingerprint *fingerprints,
				   int nr_fingerprints)
{
	int i;

	for (i = 0; i < nr_fingerprints; i++)
		free_fingerprint(&fingerprints[i]);
}