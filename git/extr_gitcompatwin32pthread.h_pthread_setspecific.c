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
typedef  int /*<<< orphan*/  pthread_key_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TlsSetValue (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline int pthread_setspecific(pthread_key_t key, const void *value)
{
	return TlsSetValue(key, (void *)value) ? 0 : EINVAL;
}