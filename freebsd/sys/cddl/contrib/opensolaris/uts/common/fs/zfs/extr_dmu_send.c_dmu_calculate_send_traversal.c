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
typedef  int /*<<< orphan*/  zilog_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct calculate_send_arg {int /*<<< orphan*/  compressed; int /*<<< orphan*/  uncompressed; } ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dnode_phys_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 scalar_t__ BP_GET_PSIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_GET_UCSIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_IS_HOLE (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
dmu_calculate_send_traversal(spa_t *spa, zilog_t *zilog, const blkptr_t *bp,
    const zbookmark_phys_t *zb, const dnode_phys_t *dnp, void *arg)
{
	struct calculate_send_arg *space = arg;
	if (bp != NULL && !BP_IS_HOLE(bp)) {
		space->uncompressed += BP_GET_UCSIZE(bp);
		space->compressed += BP_GET_PSIZE(bp);
	}
	return (0);
}