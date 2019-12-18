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
typedef  void* z_streamp ;

/* Variables and functions */
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ inflateEnd (void*) ; 
 int /*<<< orphan*/  mm_free (void*) ; 

__attribute__((used)) static void
zlib_inflate_free(void *ctx)
{
	z_streamp p = ctx;

	assert(inflateEnd(p) == Z_OK);
	mm_free(p);
}