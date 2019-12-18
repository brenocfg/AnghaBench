#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* io_vsd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_8__ {scalar_t__ zbc_injected; } ;
typedef  TYPE_2__ zio_bad_cksum_t ;
struct TYPE_9__ {int rm_ecksuminjected; } ;
typedef  TYPE_3__ raidz_map_t ;

/* Variables and functions */
 int zio_checksum_error (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int
raidz_checksum_verify(zio_t *zio)
{
	zio_bad_cksum_t zbc;
	raidz_map_t *rm = zio->io_vsd;

	int ret = zio_checksum_error(zio, &zbc);
	if (ret != 0 && zbc.zbc_injected != 0)
		rm->rm_ecksuminjected = 1;

	return (ret);
}