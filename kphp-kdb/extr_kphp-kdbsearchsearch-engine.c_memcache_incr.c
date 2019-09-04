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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ increment_rate (struct connection*,char const*,int,long long) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int verbosity ; 

int memcache_incr (struct connection *c, int op, const char *key, int len, long long arg) {
  if (len >= 4 && (!strncmp (key+1, "ate", 3))) {
    if (increment_rate (c, key, len, (op == 0) ? arg : -arg)) {
      return 0;
    }
  }

  if (verbosity > 1) {
    fprintf (stderr, "error in incr query (%s)\n", key);
  }
  return 0;

}