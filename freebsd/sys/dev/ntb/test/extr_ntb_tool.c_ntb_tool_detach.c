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
struct tool_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct tool_ctx* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tool_clear_data (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_mws (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_ntb (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_peers (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_spads (struct tool_ctx*) ; 

__attribute__((used)) static int
ntb_tool_detach(device_t dev)
{
	struct tool_ctx *tc = device_get_softc(dev);

	tool_clear_ntb(tc);

	tool_clear_spads(tc);

	tool_clear_mws(tc);

	tool_clear_peers(tc);

	tool_clear_data(tc);

	return (0);
}