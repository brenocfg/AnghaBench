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
 int AMD_CPUID_SVM_DECODE_ASSIST ; 
 int svm_feature ; 

__attribute__((used)) static __inline int
decode_assist(void)
{

	return (svm_feature & AMD_CPUID_SVM_DECODE_ASSIST);
}