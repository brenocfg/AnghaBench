#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* mc_check_perm; } ;
struct TYPE_3__ {void* rpc_check_perm; } ;

/* Variables and functions */
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_cache ; 
 int /*<<< orphan*/  disable_wildcard ; 
 int index_mode ; 
 int max_memory ; 
 void* mcs_crypted_check_perm ; 
 TYPE_2__ memcache_methods ; 
 TYPE_1__ memcache_rpc_server ; 
 int metafile_size ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  pack_file ; 
 int /*<<< orphan*/  protected_mode ; 
 int return_false_if_not_found ; 
 void* rpcs_crypted_check_perm ; 
 int tcp_maximize_buffers ; 

int f_parse_option (int val) {
  switch (val) {
  case 'f':
    return_false_if_not_found = 1;
    break;
  case 'i':
    index_mode = 1;
    break;
  case 'D':
    disable_cache ++;
    break;
  case 'm':
    max_memory = 1024 * 1024 * (long long) atoi (optarg);
    break;
  case 'P':
    pack_file = optarg;
    break;
  case 'M':
    metafile_size = 1024 * atoi (optarg);
    if (metafile_size > 1024 * 1024)
      metafile_size = 1024 * 1024;
    break;
  case 'S':
    memcache_methods.mc_check_perm = mcs_crypted_check_perm;
    memcache_rpc_server.rpc_check_perm = rpcs_crypted_check_perm;
    break;
  case 'R':
    memcache_methods.mc_check_perm = mcs_crypted_check_perm;
    memcache_rpc_server.rpc_check_perm = rpcs_crypted_check_perm;
    protected_mode ++;
    disable_wildcard ++;
    break;
  case 'w':
    disable_wildcard ++;
    break;
  case 'Q':
    tcp_maximize_buffers = 1;
    break;
  default:
    return -1;
  }
  return 0;
}