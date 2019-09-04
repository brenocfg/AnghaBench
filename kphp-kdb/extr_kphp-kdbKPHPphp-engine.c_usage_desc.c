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

void usage_desc (void) {
  printf ("\t-D<key>=<value>\tset data for ini_get\n"
    "\t-H<port>\thttp port\n"
    "\t-r<rpc_port>\trpc_port\n"
    "\t-w<host>:<port>\thost and port for client mode\n"
    "\t-q\tno sql\n"
    "\t-E<error-tag-file>\tname of file with engine tag showed on every warning\n"
    "\t-f<workers_n>\trun workers_n workers\n"
    "\t-o\trun script once\n"
    "\t-p<master_port>\tport for memcached interface to master\n"
    "\t-s<cluster_name>\tused to distinguish clusters\n"
    "\t-T<tl_config_file_name>\tname of file with TL config\n"
    "\t-t<script_time_limit>\ttime limit for script in seconds\n"
    );
}