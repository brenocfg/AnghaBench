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
struct pfioc_table {int /*<<< orphan*/  pfrio_flags; int /*<<< orphan*/  pfrio_ndel; int /*<<< orphan*/  pfrio_table; } ;
typedef  int /*<<< orphan*/  io ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct pfioc_table*,int) ; 
 int pfr_clr_tables (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pf_clear_tables(void)
{
	struct pfioc_table io;
	int error;

	bzero(&io, sizeof(io));

	error = pfr_clr_tables(&io.pfrio_table, &io.pfrio_ndel,
	    io.pfrio_flags);

	return (error);
}