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
struct malloc_type {int /*<<< orphan*/  ks_shortdesc; struct malloc_type* ks_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 struct malloc_type* kmemstatistics ; 
 int /*<<< orphan*/  malloc_mtx ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct malloc_type *
malloc_desc2type(const char *desc)
{
	struct malloc_type *mtp;

	mtx_assert(&malloc_mtx, MA_OWNED);
	for (mtp = kmemstatistics; mtp != NULL; mtp = mtp->ks_next) {
		if (strcmp(mtp->ks_shortdesc, desc) == 0)
			return (mtp);
	}
	return (NULL);
}