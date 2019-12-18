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
struct TYPE_3__ {int /*<<< orphan*/  fi_guid; } ;
typedef  TYPE_1__ zfeature_info_t ;
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 size_t SPA_FEATURES ; 
 TYPE_1__* spa_feature_table ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfeature_checks_disable ; 

boolean_t
zfeature_is_supported(const char *guid)
{
	if (zfeature_checks_disable)
		return (B_TRUE);

	for (spa_feature_t i = 0; i < SPA_FEATURES; i++) {
		zfeature_info_t *feature = &spa_feature_table[i];
		if (strcmp(guid, feature->fi_guid) == 0)
			return (B_TRUE);
	}
	return (B_FALSE);
}