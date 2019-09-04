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
struct archiver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct archiver**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_archivers ; 
 struct archiver** archivers ; 
 scalar_t__ nr_archivers ; 

void register_archiver(struct archiver *ar)
{
	ALLOC_GROW(archivers, nr_archivers + 1, alloc_archivers);
	archivers[nr_archivers++] = ar;
}