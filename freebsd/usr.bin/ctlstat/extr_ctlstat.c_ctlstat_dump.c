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
struct ctlstat_context {int cur_items; int numdevs; int /*<<< orphan*/  item_mask; struct ctl_io_stats* cur_stats; } ;
struct ctl_io_stats {int item; int /*<<< orphan*/ * dma_time; int /*<<< orphan*/ * time; scalar_t__* dmas; scalar_t__* operations; scalar_t__* bytes; } ;

/* Variables and functions */
 int CTL_STATS_NUM_TYPES ; 
 scalar_t__ F_MASK (struct ctlstat_context*) ; 
 scalar_t__ F_PORTS (struct ctlstat_context*) ; 
 int /*<<< orphan*/  PRINT_BINTIME (int /*<<< orphan*/ ) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,int) ; 
 char** iotypes ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ctlstat_dump(struct ctlstat_context *ctx)
{
	int iotype, i, n;
	struct ctl_io_stats *stats = ctx->cur_stats;

	for (i = n = 0; i < ctx->cur_items;i++) {
		if (F_MASK(ctx) && bit_test(ctx->item_mask,
		    (int)stats[i].item) == 0)
			continue;
		printf("%s %d\n", F_PORTS(ctx) ? "port" : "lun", stats[i].item);
		for (iotype = 0; iotype < CTL_STATS_NUM_TYPES; iotype++) {
			printf("  io type %d (%s)\n", iotype, iotypes[iotype]);
			printf("   bytes %ju\n", (uintmax_t)
			    stats[i].bytes[iotype]);
			printf("   operations %ju\n", (uintmax_t)
			    stats[i].operations[iotype]);
			printf("   dmas %ju\n", (uintmax_t)
			    stats[i].dmas[iotype]);
			printf("   io time ");
			PRINT_BINTIME(stats[i].time[iotype]);
			printf("\n   dma time ");
			PRINT_BINTIME(stats[i].dma_time[iotype]);
			printf("\n");
		}
		if (++n >= ctx->numdevs)
			break;
	}
}