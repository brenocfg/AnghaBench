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
typedef  int /*<<< orphan*/  time_t ;
struct packed_rrset_data {size_t count; size_t rrsig_count; int /*<<< orphan*/ * rr_len; int /*<<< orphan*/ * rr_data; } ;
struct module_env {scalar_t__* now; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ rrsig_get_expiry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static time_t
min_expiry(struct module_env* env, struct packed_rrset_data* dd)
{
	size_t i;
	int32_t t, r = 15 * 24 * 3600; /* 15 days max */
	for(i=dd->count; i<dd->count+dd->rrsig_count; i++) {
		t = rrsig_get_expiry(dd->rr_data[i], dd->rr_len[i]);
		if((int32_t)t - (int32_t)*env->now > 0) {
			t -= (int32_t)*env->now;
			if(t < r)
				r = t;
		}
	}
	return (time_t)r;
}