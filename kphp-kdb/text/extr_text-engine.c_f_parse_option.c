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
 int MAX_HOLD_ONLINE_TIME ; 
 long long MAX_METAFILE_SIZE ; 
 int MIN_HOLD_ONLINE_TIME ; 
 int /*<<< orphan*/  assert (int) ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 long long dynamic_data_buffer_size ; 
 int half_mem ; 
 int hashtags_enabled ; 
 int hold_online_time ; 
 void* http_port ; 
 int list_large_metafiles ; 
 long long metafile_alloc_threshold ; 
 int /*<<< orphan*/  optarg ; 
 int persistent_history_enabled ; 
 int search_enabled ; 
 int searchtags_enabled ; 
 int sscanf (int /*<<< orphan*/ ,char*,long long*,char*) ; 
 int test_mode ; 
 int use_stemmer ; 
 int utf8_mode ; 
 int word_split_utf8 ; 

int f_parse_option (int val) {
  long long x;
  char c;
  int i;
  switch (val) {
  case 'Z': case 'm':
    c = 0;
    assert (sscanf (optarg, "%lld%c", &x, &c) >= 1);
    switch (c | 0x20) {
      case 'k':  x <<= 10; break;
      case 'm':  x <<= 20; break;
      case 'g':  x <<= 30; break;
      case 't':  x <<= 40; break;
      default: assert (c == 0x20);
    }
    if (val == 'Z' && x >= (1LL << 20) && x <= (sizeof(long) == 4 ? (3LL << 30) : (20LL << 30))) {
      dynamic_data_buffer_size = x;
    } else if (val == 'm' && x >= MAX_METAFILE_SIZE && x < (1LL << 34)) {
      metafile_alloc_threshold = x;
    }
    break;
  case 'H':
    http_port = atoi (optarg);
    break;
  case 'T':
    test_mode = 1;
    break;
  case 'U':
    word_split_utf8 = utf8_mode = 1;
    break;
  case 'M':
    half_mem = 1;
    break;
  case 'L':
    list_large_metafiles = 1;
    break;
  case 'i':
    search_enabled = 1;
    break;
  case 'y':
    persistent_history_enabled = 1;
    break;
  case 'S':
    use_stemmer = 1;
    break;
  case 't':
    hashtags_enabled = 1;
    break;
  case 'q':
    searchtags_enabled = 1;
    break;
  case 'o':
    i = atoi (optarg);
    if (i >= MIN_HOLD_ONLINE_TIME && i <= MAX_HOLD_ONLINE_TIME) {
      hold_online_time = i;
    }
    break;
  default:
    return -1;
  }
  return 0;
}