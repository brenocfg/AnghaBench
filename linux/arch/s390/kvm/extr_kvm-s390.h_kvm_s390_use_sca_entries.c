#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int has_sigpif; } ;

/* Variables and functions */
 TYPE_1__ sclp ; 

__attribute__((used)) static inline int kvm_s390_use_sca_entries(void)
{
	/*
	 * Without SIGP interpretation, only SRS interpretation (if available)
	 * might use the entries. By not setting the entries and keeping them
	 * invalid, hardware will not access them but intercept.
	 */
	return sclp.has_sigpif;
}