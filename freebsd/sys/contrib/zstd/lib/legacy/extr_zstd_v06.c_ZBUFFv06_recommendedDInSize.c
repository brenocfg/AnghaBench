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

/* Variables and functions */
 size_t ZSTDv06_BLOCKSIZE_MAX ; 
 size_t ZSTDv06_blockHeaderSize ; 

size_t ZBUFFv06_recommendedDInSize(void)  { return ZSTDv06_BLOCKSIZE_MAX + ZSTDv06_blockHeaderSize /* block header size*/ ; }