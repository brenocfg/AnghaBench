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
struct init_ebpf_key_info_t {int /*<<< orphan*/  remote; int /*<<< orphan*/  local; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int h2o_socket_ebpf_init_key_raw (struct st_h2o_ebpf_map_key_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_ebpf_key_info(struct st_h2o_ebpf_map_key_t *key, void *_info)
{
    struct init_ebpf_key_info_t *info = _info;
    return h2o_socket_ebpf_init_key_raw(key, SOCK_DGRAM, info->local, info->remote);
}