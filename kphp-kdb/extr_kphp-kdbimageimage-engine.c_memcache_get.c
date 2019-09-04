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
struct forth_request {int res; int size; int /*<<< orphan*/ * prog; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
#define  SIGABRT 132 
#define  SIGKILL 131 
#define  SIGSEGV 130 
#define  SIGTERM 129 
#define  SIGXCPU 128 
 int /*<<< orphan*/  cmd_get ; 
 int /*<<< orphan*/  forth_request_unload_prog (struct forth_request*) ; 
 int /*<<< orphan*/  get_hits ; 
 int /*<<< orphan*/  get_missed ; 
 struct forth_request* hash_get_req_f (long long) ; 
 int image_prepare_stats (struct connection*) ; 
 int memcache_write_res (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  not_zero_exit_code ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigabrt ; 
 int /*<<< orphan*/  sigkill ; 
 int /*<<< orphan*/  sigother ; 
 int /*<<< orphan*/  sigsegv ; 
 int /*<<< orphan*/  sigterm ; 
 int /*<<< orphan*/  sigxcpu ; 
 int sscanf (char const*,char*,...) ; 
 int stat_failure_write (struct connection*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stats_buffer ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  vkprintf (3, "memcache_get_process: key='%s'\n", key);
  cmd_get++;
  long long prog_id;
  int res = -1;

  /* the most frequent request */
  if (key_len >= 8 && !memcmp (key, "request", 7) && sscanf (key + 7, "%lld", &prog_id) == 1) {
    struct forth_request *R = hash_get_req_f (prog_id);
    if (R != NULL) {
      res = R->res;
    }
    return memcache_write_res (c, key, res);
  }

  if (key_len >= 7 && !memcmp (key, "output", 6) && sscanf (key + 6, "%lld", &prog_id) == 1) {
    struct forth_request *R = hash_get_req_f (prog_id);
    if (R != NULL) {
      res = R->res;
    }
    if ((res == EXIT_SUCCESS || res == EXIT_FAILURE) && R->prog != NULL) {
      get_hits++;
      return_one_key (c, key, R->prog, R->size);
      if (R->size >= 1024) {
        forth_request_unload_prog (R);
      }
      return 0;
    }
  }

  int signo;
  if (key_len >= 18 && !memcmp (key, "last_failure_prog", 17) && sscanf (key + 17, "%d", &signo) == 1) {
    vkprintf (4, "get(\"error\", signo: %d)\n", signo);
    switch (signo) {
      case 0: return stat_failure_write (c, key, &not_zero_exit_code);
      case SIGABRT: return stat_failure_write (c, key, &sigabrt);//6
      case SIGKILL: return stat_failure_write (c, key, &sigkill);//9
      case SIGSEGV: return stat_failure_write (c, key, &sigsegv);//11
      case SIGTERM: return stat_failure_write (c, key, &sigterm);//15
      case SIGXCPU: return stat_failure_write (c, key, &sigxcpu);//24
      default: return stat_failure_write (c, key, &sigother);
    }
  }

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int stats_len = image_prepare_stats (c);
    return_one_key (c, key, stats_buffer, stats_len);
    return 0;
  }
  get_missed++;
  return 0;
}