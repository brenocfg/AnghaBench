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
typedef  int /*<<< orphan*/  uintmax_t ;
struct pfsync_tdb {int /*<<< orphan*/  cur_bytes; int /*<<< orphan*/  rpl; int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pfsync_print_tdb(netdissect_options *ndo, const void *bp)
{
	const struct pfsync_tdb *t = bp;

	ND_PRINT((ndo, "\n\tspi: 0x%08x rpl: %ju cur_bytes: %ju",
	    ntohl(t->spi), (uintmax_t )be64toh(t->rpl),
	    (uintmax_t )be64toh(t->cur_bytes)));
}