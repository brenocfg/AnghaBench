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
struct st_h2o_ebpf_map_key_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_fatal (char*) ; 

int h2o_socket_ebpf_init_key(struct st_h2o_ebpf_map_key_t *key, void *sock)
{
    h2o_fatal("unimplemented");
}