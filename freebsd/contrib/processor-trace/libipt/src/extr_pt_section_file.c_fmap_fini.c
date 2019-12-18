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
struct pt_sec_file_mapping {int /*<<< orphan*/  lock; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fmap_fini(struct pt_sec_file_mapping *mapping)
{
	if (!mapping)
		return;

	fclose(mapping->file);

#if defined(FEATURE_THREADS)

	mtx_destroy(&mapping->lock);

#endif /* defined(FEATURE_THREADS) */
}