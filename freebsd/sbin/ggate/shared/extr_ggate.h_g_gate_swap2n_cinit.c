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
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
g_gate_swap2n_cinit(struct g_gate_cinit *cinit)
{

	cinit->gc_flags = htobe64(cinit->gc_flags);
	cinit->gc_nconn = htobe16(cinit->gc_nconn);
	cinit->gc_token = htobe32(cinit->gc_token);
}