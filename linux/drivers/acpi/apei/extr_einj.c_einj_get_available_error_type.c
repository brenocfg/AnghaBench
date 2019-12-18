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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int __einj_get_available_error_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  einj_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int einj_get_available_error_type(u32 *type)
{
	int rc;

	mutex_lock(&einj_mutex);
	rc = __einj_get_available_error_type(type);
	mutex_unlock(&einj_mutex);

	return rc;
}