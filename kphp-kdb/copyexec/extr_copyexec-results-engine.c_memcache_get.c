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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_get ; 
 int copyexec_results_prepare_stats (struct connection*) ; 
 int do_set_enable (unsigned long long,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_at_prefix_length (char const*,int) ; 
 char* get_collisions_list () ; 
 char* get_dead_hosts_list (unsigned long long,int) ; 
 char* get_dead_hosts_list_full (unsigned long long,int) ; 
 char* get_disabled (unsigned long long) ; 
 char* get_hosts_list (unsigned long long,int,unsigned int,unsigned int) ; 
 char* get_hosts_list_by_status (unsigned long long,int,char*) ; 
 char* get_hosts_list_by_status_and_result (unsigned long long,int,char*,unsigned int) ; 
 char* get_results_freqs (unsigned long long,int) ; 
 char* get_status_freqs (unsigned long long,int) ; 
 char* get_status_results_freqs (unsigned long long,int) ; 
 char* get_volumes () ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int return_one_key (struct connection*,char const*,char*,int) ; 
 int sscanf (char const*,char*,unsigned long long*,...) ; 
 char* stats_buff ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  cmd_get++;
  unsigned long long volume_id = 0, random_tag = 0;
  int transaction_id = 0;
  char status[32];
  const int dog_len = get_at_prefix_length (key, key_len);
  key += dog_len;
  key_len -= dog_len;

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = copyexec_results_prepare_stats (c);
    return return_one_key (c, key - dog_len, stats_buff, len);
  }

  if (key_len >= 6 && !memcmp (key, "rfreqs", 6)) {
    if (sscanf (key + 6, "%llu,%d", &volume_id, &transaction_id) == 2) {
      char *r = get_results_freqs (volume_id, transaction_id);
      if (r) {
        return_one_key (c, key - dog_len, r, strlen (r));
        free (r);
        return 0;
      }
    }
  }

  if (key_len >= 6 && !memcmp (key, "sfreqs", 6)) {
    if (sscanf (key + 6, "%llu,%d", &volume_id, &transaction_id) == 2) {
      char *r = get_status_freqs (volume_id, transaction_id);
      if (r) {
        return_one_key (c, key - dog_len, r, strlen (r));
        free (r);
        return 0;
      }
    }
  }

  if (key_len >= 7 && !memcmp (key, "srfreqs", 7)) {
    if (sscanf (key + 7, "%llu,%d", &volume_id, &transaction_id) == 2) {
      char *r = get_status_results_freqs (volume_id, transaction_id);
      if (r) {
        return_one_key (c, key - dog_len, r, strlen (r));
        free (r);
        return 0;
      }
    }
  }

  if (key_len >= 6 && !memcmp (key, "rhosts", 6)) {
    unsigned result_or, result_and;
    if (sscanf (key + 5, "%llu,%d,%u,%u", &volume_id, &transaction_id, &result_or, &result_and) == 4) {
      char *r = get_hosts_list (volume_id, transaction_id, result_or, result_and);
      if (r) {
        return_one_key (c, key - dog_len, r, strlen (r));
        free (r);
        return 0;
      }
    }
  }

  if (key_len >= 6 && !memcmp (key, "shosts", 6)) {
    if (sscanf (key + 6, "%llu,%d,%31[a-z_]", &volume_id, &transaction_id, status) == 3) {
      char *r = get_hosts_list_by_status (volume_id, transaction_id, status);
      if (r) {
        return_one_key (c, key - dog_len, r, strlen (r));
        free (r);
        return 0;
      }
    }
  }

  if (key_len >= 7 && !memcmp (key, "srhosts", 7)) {
    unsigned result;
    if (sscanf (key + 7, "%llu,%d,%31[a-z_]:0x%x", &volume_id, &transaction_id, status, &result)== 4) {
      char *r = get_hosts_list_by_status_and_result (volume_id, transaction_id, status, result);
      if (r) {
        return_one_key (c, key - dog_len, r, strlen (r));
        free (r);
        return 0;
      }
    }
  }

  if (key_len == 7 && !memcmp (key, "volumes", 7)) {
    char *r = get_volumes ();
    if (r) {
      return_one_key (c, key - dog_len, r, strlen (r));
      free (r);
      return 0;
    }
  }

  if (key_len >= 9 && !memcmp (key, "deadhosts", 9)) {
    int delay;
    if (sscanf (key + 9, "%llu,%d", &volume_id, &delay) == 2) {
      char *r = get_dead_hosts_list (volume_id, delay);
      if (r) {
        return_one_key (c, key - dog_len, r, strlen (r));
        free (r);
        return 0;
      }
    }
  }

  if (key_len >= 14 && !memcmp (key, "deadhosts_full", 14)) {
    int delay;
    if (sscanf (key + 14, "%llu,%d", &volume_id, &delay) == 2) {
      char *r = get_dead_hosts_list_full (volume_id, delay);
      if (r) {
        return_one_key (c, key - dog_len, r, strlen (r));
        free (r);
        return 0;
      }
    }
  }

  if (key_len == 10 && !memcmp (key, "collisions", 10)){
    char *r = get_collisions_list ();
    if (r) {
      return_one_key (c, key - dog_len, r, strlen (r));
      free (r);
      return 0;
    }
  }

  if (key_len >= 6 && !memcmp (key, "enable", 6) && sscanf (key + 6, "0x%llx", &random_tag) == 1) {
    int r = do_set_enable (random_tag, 1);
    return return_one_key (c, key - dog_len, (r >= 0) ? "1" : "0", 1);
  }

  if (key_len >= 7 && !memcmp (key, "disable", 7) && sscanf (key + 7, "0x%llx", &random_tag) == 1) {
    int r = do_set_enable (random_tag, 0);
    return return_one_key (c, key - dog_len, (r >= 0) ? "1" : "0", 1);
  }

  if (key_len >= 13 && !memcmp (key, "list_disabled", 13) && sscanf (key + 13, "%llu", &volume_id) == 1) {
    char *r = get_disabled (volume_id);
    if (r != NULL) {
      return_one_key (c, key - dog_len, r, strlen (r));
      free (r);
      return 0;
    }
  }

  return 0;
}