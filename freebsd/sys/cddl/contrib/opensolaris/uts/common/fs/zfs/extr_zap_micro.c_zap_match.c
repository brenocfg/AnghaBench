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
struct TYPE_3__ {int zn_matchtype; int /*<<< orphan*/  zn_key_orig; int /*<<< orphan*/  zn_key_norm; int /*<<< orphan*/  zn_normflags; int /*<<< orphan*/  zn_zap; } ;
typedef  TYPE_1__ zap_name_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 int MT_NORMALIZE ; 
 int ZAP_FLAG_UINT64_KEY ; 
 int ZAP_MAXNAMELEN ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int zap_getflags (int /*<<< orphan*/ ) ; 
 scalar_t__ zap_normalize (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ) ; 

boolean_t
zap_match(zap_name_t *zn, const char *matchname)
{
	ASSERT(!(zap_getflags(zn->zn_zap) & ZAP_FLAG_UINT64_KEY));

	if (zn->zn_matchtype & MT_NORMALIZE) {
		char norm[ZAP_MAXNAMELEN];

		if (zap_normalize(zn->zn_zap, matchname, norm,
		    zn->zn_normflags) != 0)
			return (B_FALSE);

		return (strcmp(zn->zn_key_norm, norm) == 0);
	} else {
		return (strcmp(zn->zn_key_orig, matchname) == 0);
	}
}