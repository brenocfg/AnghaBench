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
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CACHE ; 
 int /*<<< orphan*/  NFDCACHE ; 
 int /*<<< orphan*/  fdesc_hashmtx ; 
 int /*<<< orphan*/  fdhash ; 
 int /*<<< orphan*/  fdhashtbl ; 
 int /*<<< orphan*/  hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
fdesc_init(struct vfsconf *vfsp)
{

	mtx_init(&fdesc_hashmtx, "fdescfs_hash", NULL, MTX_DEF);
	fdhashtbl = hashinit(NFDCACHE, M_CACHE, &fdhash);
	return (0);
}