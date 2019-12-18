#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ spa_errlog_scrub; scalar_t__ spa_errlog_last; int /*<<< orphan*/  spa_errlist_lock; int /*<<< orphan*/  spa_errlist_scrub; int /*<<< orphan*/  spa_errlist_last; int /*<<< orphan*/  spa_errlog_lock; int /*<<< orphan*/  spa_meta_objset; int /*<<< orphan*/  spa_scrub_finished; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zap_count (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

uint64_t
spa_get_errlog_size(spa_t *spa)
{
	uint64_t total = 0, count;

	mutex_enter(&spa->spa_errlog_lock);
	if (spa->spa_errlog_scrub != 0 &&
	    zap_count(spa->spa_meta_objset, spa->spa_errlog_scrub,
	    &count) == 0)
		total += count;

	if (spa->spa_errlog_last != 0 && !spa->spa_scrub_finished &&
	    zap_count(spa->spa_meta_objset, spa->spa_errlog_last,
	    &count) == 0)
		total += count;
	mutex_exit(&spa->spa_errlog_lock);

	mutex_enter(&spa->spa_errlist_lock);
	total += avl_numnodes(&spa->spa_errlist_last);
	total += avl_numnodes(&spa->spa_errlist_scrub);
	mutex_exit(&spa->spa_errlist_lock);

	return (total);
}