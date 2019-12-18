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
typedef  int /*<<< orphan*/  ufs_lbn_t ;
typedef  int ufs2_daddr_t ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  fsbtodb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jblocks_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suj_jblocks ; 

__attribute__((used)) static void
suj_add_block(ino_t ino, ufs_lbn_t lbn, ufs2_daddr_t blk, int frags)
{

	jblocks_add(suj_jblocks, fsbtodb(fs, blk), fsbtodb(fs, frags));
}