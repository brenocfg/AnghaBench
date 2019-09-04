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
 int check_privacy (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int parse_privacy_key (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,char*,int) ; 
 int sscanf (char const*,char*,int*,int*,int*) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void exec_get_check_privacy (struct connection *c, const char *str, int len) {
  int checker_id, user_id, i, j, k;
  privacy_key_t privacy_key;

  if (sscanf (str, "%d~%d:%n", &checker_id, &user_id, &i) >= 2 && (j = parse_privacy_key (str+i, &privacy_key, -1)) > 0) {
    j += i;
    if (!str[j]) {
      i = check_privacy (checker_id, user_id, privacy_key);
      if (verbosity > 1) {
        fprintf (stderr, "check_privacy(%d,%d,%016llx) = %d\n", checker_id, user_id, privacy_key, i);
      }
      stats_buff[0] = (i & -4 ? '?' : '0' + i);
      stats_buff[1] = 0;

      return_one_key (c, str, stats_buff, 1);
      return;
    } else if (str[j] == ',') {
      k = 0;
      while (k < 256) {
        i = check_privacy (checker_id, user_id, privacy_key);
        stats_buff[k++] = (i & -4 ? '?' : '0' + i);
        if (verbosity > 1) {
          fprintf (stderr, "check_privacy(%d,%d,%016llx) = %d\n", checker_id, user_id, privacy_key, i);
        }
        if (str[j] != ',') {
          break;
        }
        i = parse_privacy_key (str+j+1, &privacy_key, -1);
        if (i <= 0) {
          break;
        }
        j = j+i+1;
      }
      if (!str[j]) {
        stats_buff[k] = 0;
        return_one_key (c, str, stats_buff, k);
        return;
      }
    }
  }
  return;
}