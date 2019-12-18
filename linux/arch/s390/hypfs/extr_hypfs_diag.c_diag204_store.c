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

/* Variables and functions */
 void* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (void*) ; 
 int diag204_do_store (void*,int) ; 
 void* diag204_get_buffer (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  diag204_info_type ; 

__attribute__((used)) static void *diag204_store(void)
{
	void *buf;
	int pages, rc;

	buf = diag204_get_buffer(diag204_info_type, &pages);
	if (IS_ERR(buf))
		goto out;
	rc = diag204_do_store(buf, pages);
	if (rc)
		return ERR_PTR(rc);
out:
	return buf;
}