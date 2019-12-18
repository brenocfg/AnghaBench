#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_5__ {int za_integer_length; int za_num_integers; scalar_t__ za_first_integer; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  spa_feat_desc_obj; int /*<<< orphan*/  spa_feat_for_read_obj; int /*<<< orphan*/  spa_feat_for_write_obj; int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  zfeature_is_supported (int /*<<< orphan*/ ) ; 

boolean_t
spa_features_check(spa_t *spa, boolean_t for_write,
    nvlist_t *unsup_feat, nvlist_t *enabled_feat)
{
	objset_t *os = spa->spa_meta_objset;
	boolean_t supported;
	zap_cursor_t zc;
	zap_attribute_t za;
	uint64_t obj = for_write ?
	    spa->spa_feat_for_write_obj : spa->spa_feat_for_read_obj;

	supported = B_TRUE;
	for (zap_cursor_init(&zc, os, obj);
	    zap_cursor_retrieve(&zc, &za) == 0;
	    zap_cursor_advance(&zc)) {
		ASSERT(za.za_integer_length == sizeof (uint64_t) &&
		    za.za_num_integers == 1);

		if (NULL != enabled_feat) {
			fnvlist_add_uint64(enabled_feat, za.za_name,
			    za.za_first_integer);
		}

		if (za.za_first_integer != 0 &&
		    !zfeature_is_supported(za.za_name)) {
			supported = B_FALSE;

			if (NULL != unsup_feat) {
				char *desc = "";
				char buf[MAXPATHLEN];

				if (zap_lookup(os, spa->spa_feat_desc_obj,
				    za.za_name, 1, sizeof (buf), buf) == 0)
					desc = buf;

				VERIFY(nvlist_add_string(unsup_feat, za.za_name,
				    desc) == 0);
			}
		}
	}
	zap_cursor_fini(&zc);

	return (supported);
}