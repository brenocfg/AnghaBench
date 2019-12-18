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
struct TYPE_5__ {int /*<<< orphan*/  (* ci_tmpl_free ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ zio_checksum_info_t ;
struct TYPE_6__ {int /*<<< orphan*/ ** spa_cksum_tmpls; } ;
typedef  TYPE_2__ spa_t ;
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int ZIO_CHECKSUM_FUNCTIONS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* zio_checksum_table ; 

void
zio_checksum_templates_free(spa_t *spa)
{
	for (enum zio_checksum checksum = 0;
	    checksum < ZIO_CHECKSUM_FUNCTIONS; checksum++) {
		if (spa->spa_cksum_tmpls[checksum] != NULL) {
			zio_checksum_info_t *ci = &zio_checksum_table[checksum];

			VERIFY(ci->ci_tmpl_free != NULL);
			ci->ci_tmpl_free(spa->spa_cksum_tmpls[checksum]);
			spa->spa_cksum_tmpls[checksum] = NULL;
		}
	}
}