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
struct tool_ctx {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct tool_ctx* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int tool_check_ntb (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_data (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_mws (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_peers (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_spads (struct tool_ctx*) ; 
 int tool_init_mws (struct tool_ctx*) ; 
 int tool_init_ntb (struct tool_ctx*) ; 
 int tool_init_peers (struct tool_ctx*) ; 
 int tool_init_spads (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_setup_sysctl (struct tool_ctx*) ; 

__attribute__((used)) static int
ntb_tool_attach(device_t dev)
{
	struct tool_ctx *tc = device_get_softc(dev);
	int rc = 0;

	tc->dev = dev;
	rc = tool_check_ntb(tc);
	if (rc)
		goto out;

	rc = tool_init_peers(tc);
	if (rc)
		goto err_clear_data;

	rc = tool_init_mws(tc);
	if (rc)
		goto err_clear_data;

	rc = tool_init_spads(tc);
	if (rc)
		goto err_clear_mws;

	rc = tool_init_ntb(tc);
	if (rc)
		goto err_clear_spads;

	tool_setup_sysctl(tc);

	return (0);

err_clear_spads:
	tool_clear_spads(tc);
err_clear_mws:
	tool_clear_mws(tc);
	tool_clear_peers(tc);
err_clear_data:
	tool_clear_data(tc);
out:
	device_printf(dev, "ntb_tool attached failed with err=(%d).\n", rc);
	return (rc);
}