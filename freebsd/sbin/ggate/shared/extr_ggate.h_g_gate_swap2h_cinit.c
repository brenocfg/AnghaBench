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
struct g_gate_cinit {int /*<<< orphan*/  gc_token; int /*<<< orphan*/  gc_nconn; int /*<<< orphan*/  gc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
g_gate_swap2h_cinit(struct g_gate_cinit *cinit)
{

	cinit->gc_flags = be64toh(cinit->gc_flags);
	cinit->gc_nconn = be16toh(cinit->gc_nconn);
	cinit->gc_token = be32toh(cinit->gc_token);
}