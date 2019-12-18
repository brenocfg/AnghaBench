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
struct event_debug_entry {scalar_t__ ptr; } ;
typedef  int /*<<< orphan*/  ev_uintptr_t ;

/* Variables and functions */

__attribute__((used)) static inline unsigned
hash_debug_entry(const struct event_debug_entry *e)
{
	/* We need to do this silliness to convince compilers that we
	 * honestly mean to cast e->ptr to an integer, and discard any
	 * part of it that doesn't fit in an unsigned.
	 */
	unsigned u = (unsigned) ((ev_uintptr_t) e->ptr);
	/* Our hashtable implementation is pretty sensitive to low bits,
	 * and every struct event is over 64 bytes in size, so we can
	 * just say >>6. */
	return (u >> 6);
}