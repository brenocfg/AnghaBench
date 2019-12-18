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
typedef  int /*<<< orphan*/  zap_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int ZAP_FLAG_HASH64 ; 
 int zap_getflags (int /*<<< orphan*/ *) ; 

uint32_t
zap_maxcd(zap_t *zap)
{
	if (zap_getflags(zap) & ZAP_FLAG_HASH64)
		return ((1<<16)-1);
	else
		return (-1U);
}