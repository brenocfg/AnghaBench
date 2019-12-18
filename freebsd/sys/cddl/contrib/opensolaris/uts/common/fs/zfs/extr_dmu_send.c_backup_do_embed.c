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
struct TYPE_3__ {int dsa_featureflags; } ;
typedef  TYPE_1__ dmu_sendarg_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int BPE_GET_ETYPE (int /*<<< orphan*/  const*) ; 
#define  BP_EMBEDDED_TYPE_DATA 128 
 scalar_t__ BP_GET_COMPRESS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_IS_EMBEDDED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int DMU_BACKUP_FEATURE_EMBED_DATA ; 
 int DMU_BACKUP_FEATURE_LZ4 ; 
 scalar_t__ ZIO_COMPRESS_LEGACY_FUNCTIONS ; 

__attribute__((used)) static boolean_t
backup_do_embed(dmu_sendarg_t *dsp, const blkptr_t *bp)
{
	if (!BP_IS_EMBEDDED(bp))
		return (B_FALSE);

	/*
	 * Compression function must be legacy, or explicitly enabled.
	 */
	if ((BP_GET_COMPRESS(bp) >= ZIO_COMPRESS_LEGACY_FUNCTIONS &&
	    !(dsp->dsa_featureflags & DMU_BACKUP_FEATURE_LZ4)))
		return (B_FALSE);

	/*
	 * Embed type must be explicitly enabled.
	 */
	switch (BPE_GET_ETYPE(bp)) {
	case BP_EMBEDDED_TYPE_DATA:
		if (dsp->dsa_featureflags & DMU_BACKUP_FEATURE_EMBED_DATA)
			return (B_TRUE);
		break;
	default:
		return (B_FALSE);
	}
	return (B_FALSE);
}