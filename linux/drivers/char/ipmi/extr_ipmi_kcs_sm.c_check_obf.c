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
struct si_sm_data {scalar_t__ obf_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_STATUS_OBF (unsigned char) ; 
 void* OBF_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  start_error_recovery (struct si_sm_data*,char*) ; 

__attribute__((used)) static inline int check_obf(struct si_sm_data *kcs, unsigned char status,
			    long time)
{
	if (!GET_STATUS_OBF(status)) {
		kcs->obf_timeout -= time;
		if (kcs->obf_timeout < 0) {
			kcs->obf_timeout = OBF_RETRY_TIMEOUT;
			start_error_recovery(kcs, "OBF not ready in time");
			return 1;
		}
		return 0;
	}
	kcs->obf_timeout = OBF_RETRY_TIMEOUT;
	return 1;
}