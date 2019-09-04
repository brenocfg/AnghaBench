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
typedef  int /*<<< orphan*/  privacy_key_t ;

/* Variables and functions */
 scalar_t__ parse_privacy_key (char const*,int /*<<< orphan*/ *,int) ; 
 int prepare_privacy_str (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,char*,int) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 char* stats_buff ; 

void exec_get_privacy (struct connection *c, const char *str, int len) {
  int user_id, i;
  privacy_key_t privacy_key;

  if (sscanf (str, "privacy%d_%n", &user_id, &i) >= 1 && parse_privacy_key (str+i, &privacy_key, 1) > 0) {
    i = prepare_privacy_str (stats_buff, user_id, privacy_key);
    if (i >= 0) {
      return_one_key (c, str, stats_buff, i);
    } else {
      return_one_key (c, str, "?", 1);
    }
    return;
  }
  return;
}