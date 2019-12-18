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
struct g_gate_sinit {int /*<<< orphan*/  gs_error; int /*<<< orphan*/  gs_sectorsize; int /*<<< orphan*/  gs_mediasize; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
g_gate_swap2h_sinit(struct g_gate_sinit *sinit)
{

	/* Swap only used fields. */
	sinit->gs_mediasize = be64toh(sinit->gs_mediasize);
	sinit->gs_sectorsize = be32toh(sinit->gs_sectorsize);
	sinit->gs_error = be16toh(sinit->gs_error);
}