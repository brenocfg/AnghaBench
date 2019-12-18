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
struct si_sm_data {scalar_t__ ibf_timeout; } ;

/* Variables and functions */
 scalar_t__ GET_STATUS_IBF (unsigned char) ; 
 void* IBF_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  start_error_recovery (struct si_sm_data*,char*) ; 

__attribute__((used)) static inline int check_ibf(struct si_sm_data *kcs, unsigned char status,
			    long time)
{
	if (GET_STATUS_IBF(status)) {
		kcs->ibf_timeout -= time;
		if (kcs->ibf_timeout < 0) {
			start_error_recovery(kcs, "IBF not ready in time");
			kcs->ibf_timeout = IBF_RETRY_TIMEOUT;
			return 1;
		}
		return 0;
	}
	kcs->ibf_timeout = IBF_RETRY_TIMEOUT;
	return 1;
}