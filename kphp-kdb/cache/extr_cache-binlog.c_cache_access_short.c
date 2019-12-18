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
struct lev_cache_access_short {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  a2hex (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ dump_line_header (char*) ; 
 int /*<<< orphan*/  filtered_uri_short_md5 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cache_access_short (struct lev_cache_access_short *E, int t) {
  char output[33];
  a2hex (E->data, 8, output);
  if (!strncmp (output, filtered_uri_short_md5, 16)) {
    if (dump_line_header ("LEV_CACHE_ACCESS_SHORT")) {
      fprintf (out, "+%d\t%s\n", t, output);
    }
  }
}