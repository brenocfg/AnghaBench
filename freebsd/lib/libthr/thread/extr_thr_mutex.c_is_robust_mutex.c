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
struct TYPE_2__ {int m_flags; } ;
struct pthread_mutex {TYPE_1__ m_lock; } ;

/* Variables and functions */
 int UMUTEX_ROBUST ; 

__attribute__((used)) static bool
is_robust_mutex(struct pthread_mutex *m)
{

	return ((m->m_lock.m_flags & UMUTEX_ROBUST) != 0);
}