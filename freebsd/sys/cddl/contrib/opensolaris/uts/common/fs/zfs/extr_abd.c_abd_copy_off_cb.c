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
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static int
abd_copy_off_cb(void *dbuf, void *sbuf, size_t size, void *private)
{
	(void) memcpy(dbuf, sbuf, size);
	return (0);
}