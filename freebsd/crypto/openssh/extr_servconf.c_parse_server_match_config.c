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
struct connection_info {int dummy; } ;
typedef  int /*<<< orphan*/  ServerOptions ;

/* Variables and functions */
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  copy_set_server_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_server_options (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_server_config (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct connection_info*) ; 

void
parse_server_match_config(ServerOptions *options,
   struct connection_info *connectinfo)
{
	ServerOptions mo;

	initialize_server_options(&mo);
	parse_server_config(&mo, "reprocess config", cfg, connectinfo);
	copy_set_server_options(options, &mo, 0);
}