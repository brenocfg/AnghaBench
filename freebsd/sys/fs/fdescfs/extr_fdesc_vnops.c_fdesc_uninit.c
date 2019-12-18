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
struct vfsconf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CACHE ; 
 int /*<<< orphan*/  fdesc_hashmtx ; 
 int /*<<< orphan*/  fdhash ; 
 int /*<<< orphan*/  fdhashtbl ; 
 int /*<<< orphan*/  hashdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

int
fdesc_uninit(struct vfsconf *vfsp)
{

	hashdestroy(fdhashtbl, M_CACHE, fdhash);
	mtx_destroy(&fdesc_hashmtx);
	return (0);
}