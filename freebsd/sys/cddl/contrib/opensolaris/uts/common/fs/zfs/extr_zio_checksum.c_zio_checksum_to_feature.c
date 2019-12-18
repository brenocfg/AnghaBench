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
typedef  int /*<<< orphan*/  spa_feature_t ;
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_FEATURE_EDONR ; 
 int /*<<< orphan*/  SPA_FEATURE_NONE ; 
 int /*<<< orphan*/  SPA_FEATURE_SHA512 ; 
 int /*<<< orphan*/  SPA_FEATURE_SKEIN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
#define  ZIO_CHECKSUM_EDONR 130 
 int ZIO_CHECKSUM_MASK ; 
#define  ZIO_CHECKSUM_SHA512 129 
#define  ZIO_CHECKSUM_SKEIN 128 

spa_feature_t
zio_checksum_to_feature(enum zio_checksum cksum)
{
	VERIFY((cksum & ~ZIO_CHECKSUM_MASK) == 0);

	switch (cksum) {
	case ZIO_CHECKSUM_SHA512:
		return (SPA_FEATURE_SHA512);
	case ZIO_CHECKSUM_SKEIN:
		return (SPA_FEATURE_SKEIN);
#ifdef illumos
	case ZIO_CHECKSUM_EDONR:
		return (SPA_FEATURE_EDONR);
#endif
	}
	return (SPA_FEATURE_NONE);
}