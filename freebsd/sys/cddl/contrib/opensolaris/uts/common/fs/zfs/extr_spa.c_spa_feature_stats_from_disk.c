#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_6__ {int za_integer_length; int za_num_integers; int /*<<< orphan*/  za_first_integer; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  spa_feat_for_write_obj; int /*<<< orphan*/  spa_meta_objset; int /*<<< orphan*/  spa_feat_for_read_obj; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
spa_feature_stats_from_disk(spa_t *spa, nvlist_t *features)
{
	zap_cursor_t zc;
	zap_attribute_t za;

	/* We may be unable to read features if pool is suspended. */
	if (spa_suspended(spa))
		return;

	if (spa->spa_feat_for_read_obj != 0) {
		for (zap_cursor_init(&zc, spa->spa_meta_objset,
		    spa->spa_feat_for_read_obj);
		    zap_cursor_retrieve(&zc, &za) == 0;
		    zap_cursor_advance(&zc)) {
			ASSERT(za.za_integer_length == sizeof (uint64_t) &&
			    za.za_num_integers == 1);
			VERIFY0(nvlist_add_uint64(features, za.za_name,
			    za.za_first_integer));
		}
		zap_cursor_fini(&zc);
	}

	if (spa->spa_feat_for_write_obj != 0) {
		for (zap_cursor_init(&zc, spa->spa_meta_objset,
		    spa->spa_feat_for_write_obj);
		    zap_cursor_retrieve(&zc, &za) == 0;
		    zap_cursor_advance(&zc)) {
			ASSERT(za.za_integer_length == sizeof (uint64_t) &&
			    za.za_num_integers == 1);
			VERIFY0(nvlist_add_uint64(features, za.za_name,
			    za.za_first_integer));
		}
		zap_cursor_fini(&zc);
	}
}