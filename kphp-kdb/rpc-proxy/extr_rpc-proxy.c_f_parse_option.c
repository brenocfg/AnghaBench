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
 void* PING_INTERVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 void* atof (int /*<<< orphan*/ ) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int binlog_cyclic_mode ; 
 int binlog_mode_on ; 
 int /*<<< orphan*/  bname ; 
 long long dynamic_data_buffer_size ; 
 int /*<<< orphan*/  errno ; 
 long long max_binlog_size ; 
 int /*<<< orphan*/  nice (int) ; 
 int /*<<< orphan*/  only_first_cluster ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 void* ping_interval ; 
 int rpc_crc32_mode ; 
 int rpc_disable_crc32_check ; 
 int sscanf (int /*<<< orphan*/ ,char*,long long*,char*) ; 
 int /*<<< orphan*/  tcp_buffers ; 
 int /*<<< orphan*/  test_mode ; 
 void* vv_tl_drop_probability ; 

int f_parse_option (int val) {
  char c;
  long long x;
  switch (val) {
  case 'f':
    only_first_cluster ++;
    return 0;
  case 'T':
    ++test_mode;
    return 0;
  case 'N':
    tcp_buffers ++;
    return 0;
  case 'C':
    rpc_crc32_mode = atoi (optarg);
    rpc_disable_crc32_check = (rpc_crc32_mode & 1);
    return 0;
  case 'H': case 'S':
    c = 0;
    assert (sscanf (optarg, "%lld%c", &x, &c) >= 1);
    switch (c | 0x20) {
      case 'k':  x <<= 10; break;
      case 'm':  x <<= 20; break;
      case 'g':  x <<= 30; break;
      case 't':  x <<= 40; break;
      default: assert (c == 0x20);
    }
    if (val == 'H') {
      if (x >= (1LL << 20) && x <= (sizeof(long) == 4 ? (3LL << 30) : (100LL << 30))) {
        dynamic_data_buffer_size = x;
      }
    } else if (val == 'S') {
      max_binlog_size = x;
    }
    break;
  case 'y':
    ping_interval = atof (optarg);
    if (ping_interval <= 0) { ping_interval = PING_INTERVAL; }
    break;
  case 'B':
    bname = optarg;
    binlog_cyclic_mode = 1;
    binlog_mode_on |= 1;
    //max_binlog_size = 100000;
    break;
  case 'F':
    binlog_mode_on |= 2;
    break;
  case 'Q':
    vv_tl_drop_probability = atof (optarg);
    break;
  case 'n':
    errno = 0;
    nice (atoi (optarg));
    if (errno) {
      perror ("nice");
    }
    break;
  default:
    return -1;
  }
  return 0;
}