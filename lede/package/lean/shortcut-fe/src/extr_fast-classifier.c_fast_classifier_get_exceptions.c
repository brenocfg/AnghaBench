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
struct fast_classifier {int* exceptions; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int FAST_CL_EXCEPTION_MAX ; 
 int PAGE_SIZE ; 
 struct fast_classifier __fsc ; 
 char** fast_classifier_exception_events_string ; 
 scalar_t__ snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t fast_classifier_get_exceptions(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	int idx, len;
	struct fast_classifier *sc = &__fsc;

	spin_lock_bh(&sc->lock);
	for (len = 0, idx = 0; idx < FAST_CL_EXCEPTION_MAX; idx++) {
		if (sc->exceptions[idx]) {
			len += snprintf(buf + len, (ssize_t)(PAGE_SIZE - len), "%s = %d\n", fast_classifier_exception_events_string[idx], sc->exceptions[idx]);
		}
	}
	spin_unlock_bh(&sc->lock);

	return len;
}