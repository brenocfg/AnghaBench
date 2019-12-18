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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int MC_RAW_WR ; 
 int mbuf_cflags (struct mbuf*) ; 
 scalar_t__ needs_tso (struct mbuf*) ; 

__attribute__((used)) static inline int
cannot_use_txpkts(struct mbuf *m)
{
	/* maybe put a GL limit too, to avoid silliness? */

	return (needs_tso(m) || (mbuf_cflags(m) & MC_RAW_WR) != 0);
}