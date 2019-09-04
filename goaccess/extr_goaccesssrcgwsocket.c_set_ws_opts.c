#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sslkey; scalar_t__ sslcert; scalar_t__ port; scalar_t__ origin; scalar_t__ fifo_out; scalar_t__ fifo_in; scalar_t__ addr; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  ws_set_config_host (scalar_t__) ; 
 int /*<<< orphan*/  ws_set_config_origin (scalar_t__) ; 
 int /*<<< orphan*/  ws_set_config_pipein (scalar_t__) ; 
 int /*<<< orphan*/  ws_set_config_pipeout (scalar_t__) ; 
 int /*<<< orphan*/  ws_set_config_port (scalar_t__) ; 
 int /*<<< orphan*/  ws_set_config_sslcert (scalar_t__) ; 
 int /*<<< orphan*/  ws_set_config_sslkey (scalar_t__) ; 
 int /*<<< orphan*/  ws_set_config_strict (int) ; 

__attribute__((used)) static void
set_ws_opts (void)
{
  ws_set_config_strict (1);
  if (conf.addr)
    ws_set_config_host (conf.addr);
  if (conf.fifo_in)
    ws_set_config_pipein (conf.fifo_in);
  if (conf.fifo_out)
    ws_set_config_pipeout (conf.fifo_out);
  if (conf.origin)
    ws_set_config_origin (conf.origin);
  if (conf.port)
    ws_set_config_port (conf.port);
  if (conf.sslcert)
    ws_set_config_sslcert (conf.sslcert);
  if (conf.sslkey)
    ws_set_config_sslkey (conf.sslkey);
}