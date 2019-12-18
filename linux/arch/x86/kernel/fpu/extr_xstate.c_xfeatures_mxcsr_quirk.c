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
typedef  int u64 ;

/* Variables and functions */
 int XFEATURE_MASK_FP ; 
 int XFEATURE_MASK_SSE ; 
 int XFEATURE_MASK_YMM ; 

__attribute__((used)) static inline bool xfeatures_mxcsr_quirk(u64 xfeatures)
{
	if (!(xfeatures & (XFEATURE_MASK_SSE|XFEATURE_MASK_YMM)))
		return false;

	if (xfeatures & XFEATURE_MASK_FP)
		return false;

	return true;
}