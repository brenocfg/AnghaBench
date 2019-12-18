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
struct TYPE_3__ {int /*<<< orphan*/  cctx; int /*<<< orphan*/  dstBuffer; int /*<<< orphan*/  srcBuffer; } ;
typedef  TYPE_1__ cRess_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_freeCStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void FIO_freeCResources(cRess_t ress)
{
    free(ress.srcBuffer);
    free(ress.dstBuffer);
    ZSTD_freeCStream(ress.cctx);   /* never fails */
}