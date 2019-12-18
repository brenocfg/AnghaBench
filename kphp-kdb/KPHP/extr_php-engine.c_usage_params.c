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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

void usage_params (void) {
  printf ("[-H<port>] [-r<rpc_port>] [-w<host>:<port>] [-q] [f<workers_n>] [-D<key>=<value>] [-o] [-p<master_port>] [-s<cluster_name>] [-T<tl_config_file_name>] [-t<script_time_limit>]");
}