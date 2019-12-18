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
typedef  scalar_t__ heim_base_atomic_type ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _heim_base_mutex ; 

__attribute__((used)) static inline heim_base_atomic_type
heim_base_atomic_dec(heim_base_atomic_type *x)
{
    heim_base_atomic_type t;
    HEIMDAL_MUTEX_lock(&_heim_base_mutex);
    t = --(*x);
    HEIMDAL_MUTEX_unlock(&_heim_base_mutex);
    return t;
}