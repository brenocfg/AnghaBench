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
struct pthread_mutex_attr {scalar_t__ m_type; scalar_t__ m_protocol; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PTHREAD_MUTEX_ERRORCHECK ; 
 scalar_t__ PTHREAD_MUTEX_TYPE_MAX ; 
 scalar_t__ PTHREAD_PRIO_NONE ; 
 scalar_t__ PTHREAD_PRIO_PROTECT ; 

__attribute__((used)) static int
mutex_check_attr(const struct pthread_mutex_attr *attr)
{

	if (attr->m_type < PTHREAD_MUTEX_ERRORCHECK ||
	    attr->m_type >= PTHREAD_MUTEX_TYPE_MAX)
		return (EINVAL);
	if (attr->m_protocol < PTHREAD_PRIO_NONE ||
	    attr->m_protocol > PTHREAD_PRIO_PROTECT)
		return (EINVAL);
	return (0);
}