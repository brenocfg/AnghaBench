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
struct lev_cache_set_size_short {int size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  a2hex (unsigned char*,int,char*) ; 
 scalar_t__ dump_line_header (char*) ; 
 int /*<<< orphan*/  filtered_uri_short_md5 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

void cache_set_size_short (struct lev_cache_set_size_short *E) {
  char output[33];
  a2hex ((unsigned char *) E->data, 8, output);
  if (!strncmp (output, filtered_uri_short_md5, 16)) {
    if (dump_line_header ("LEV_CACHE_SET_SIZE_SHORT")) {
      fprintf (out, "\t%s\t%d\n", output, E->size);
    }
  }
}