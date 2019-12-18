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
struct isis_metric_block {int /*<<< orphan*/  metric_error; int /*<<< orphan*/  metric_expense; int /*<<< orphan*/  metric_delay; int /*<<< orphan*/  metric_default; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ ISIS_LSP_TLV_METRIC_IE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISIS_LSP_TLV_METRIC_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISIS_LSP_TLV_METRIC_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isis_print_metric_block(netdissect_options *ndo,
                        const struct isis_metric_block *isis_metric_block)
{
    ND_PRINT((ndo, ", Default Metric: %d, %s",
           ISIS_LSP_TLV_METRIC_VALUE(isis_metric_block->metric_default),
           ISIS_LSP_TLV_METRIC_IE(isis_metric_block->metric_default) ? "External" : "Internal"));
    if (!ISIS_LSP_TLV_METRIC_SUPPORTED(isis_metric_block->metric_delay))
        ND_PRINT((ndo, "\n\t\t  Delay Metric: %d, %s",
               ISIS_LSP_TLV_METRIC_VALUE(isis_metric_block->metric_delay),
               ISIS_LSP_TLV_METRIC_IE(isis_metric_block->metric_delay) ? "External" : "Internal"));
    if (!ISIS_LSP_TLV_METRIC_SUPPORTED(isis_metric_block->metric_expense))
        ND_PRINT((ndo, "\n\t\t  Expense Metric: %d, %s",
               ISIS_LSP_TLV_METRIC_VALUE(isis_metric_block->metric_expense),
               ISIS_LSP_TLV_METRIC_IE(isis_metric_block->metric_expense) ? "External" : "Internal"));
    if (!ISIS_LSP_TLV_METRIC_SUPPORTED(isis_metric_block->metric_error))
        ND_PRINT((ndo, "\n\t\t  Error Metric: %d, %s",
               ISIS_LSP_TLV_METRIC_VALUE(isis_metric_block->metric_error),
               ISIS_LSP_TLV_METRIC_IE(isis_metric_block->metric_error) ? "External" : "Internal"));

    return(1); /* everything is ok */
}