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
typedef  int /*<<< orphan*/  ZSTD_DStream ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/ * ZSTD_createDStream_advanced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_defaultCMem ; 

ZSTD_DStream* ZSTD_createDStream(void)
{
    DEBUGLOG(3, "ZSTD_createDStream");
    return ZSTD_createDStream_advanced(ZSTD_defaultCMem);
}