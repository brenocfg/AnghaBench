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
struct keep_mc_store {int text_id; int* res; } ;
struct connection {TYPE_1__* Tmp; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  cmd_get ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 
 int get_at_prefix_length (char const*,int) ; 
 int /*<<< orphan*/  get_hits ; 
 int /*<<< orphan*/  get_missed ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int return_one_key (struct connection*,char const*,scalar_t__,int) ; 
 int spell_get_dicts (scalar_t__,int /*<<< orphan*/ ) ; 
 int spell_prepare_stats (struct connection*) ; 
 int sprintf (scalar_t__,char*,int,int,int) ; 
 int sscanf (char const*,char*,int*) ; 
 scalar_t__ stats_buff ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 scalar_t__ test_mode ; 
 scalar_t__ worst_misspell_msg ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  cmd_get++;
  int dog_len = get_at_prefix_length (key, key_len);
  key += dog_len;
  key_len -= dog_len;
  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int stats_len = spell_prepare_stats (c);
    return_one_key (c, key - dog_len, stats_buff, stats_len);
    return 0;
  }
  struct keep_mc_store *Data = 0;
  if (c->Tmp) {
    Data = (struct keep_mc_store *) c->Tmp->start;
  }
  int text_id;
  if (Data && sscanf (key, "request%d", &text_id) == 1 && Data->text_id == text_id) {
    get_hits++;
    return return_one_key (c, key - dog_len, stats_buff, sprintf (stats_buff, "%d,%d,%d", Data->res[0], Data->res[1], Data->res[2]));
  }
  if (key_len == 5 && !memcmp (key, "dicts", 5)) {
  int l = spell_get_dicts (stats_buff, STATS_BUFF_SIZE);
    get_hits++;
    return return_one_key (c, key - dog_len, stats_buff, l);
  }
  if (test_mode && worst_misspell_msg && key_len == 18 && !memcmp (key, "worst_misspell_msg", 18)) {
    get_hits++;
    return return_one_key (c, key - dog_len, worst_misspell_msg,strlen (worst_misspell_msg));
  }
  free_tmp_buffers (c);
  get_missed++;
  return 0;
}