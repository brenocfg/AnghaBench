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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int zio_checksum_verify (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*) ; 

__attribute__((used)) static int
raidz_checksum_verify(const spa_t *spa, const blkptr_t *bp, void *data,
    uint64_t size)
{
	return (zio_checksum_verify(spa, bp, data));
}