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
 int /*<<< orphan*/  evutil_secure_rng_get_bytes (void*,size_t) ; 

__attribute__((used)) static void
arc4random_buf(void *buf, size_t nbytes)
{
	evutil_secure_rng_get_bytes(buf, nbytes);
	return;
}