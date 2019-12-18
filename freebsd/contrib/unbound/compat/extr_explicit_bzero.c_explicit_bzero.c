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
 int /*<<< orphan*/  SecureZeroMemory (void*,size_t) ; 
 int /*<<< orphan*/  __explicit_bzero_hook (void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void
explicit_bzero(void *buf, size_t len)
{
#ifdef UB_ON_WINDOWS
	SecureZeroMemory(buf, len);
#endif
	memset(buf, 0, len);
	__explicit_bzero_hook(buf, len);
}