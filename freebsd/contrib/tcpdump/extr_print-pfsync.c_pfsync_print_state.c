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
struct pfsync_state {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  print_state (int /*<<< orphan*/ *,struct pfsync_state*) ; 
 int /*<<< orphan*/  safeputchar (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void
pfsync_print_state(netdissect_options *ndo, const void *bp)
{
	struct pfsync_state *st = (struct pfsync_state *)bp;

	safeputchar(ndo, '\n');
	print_state(ndo, st);
}