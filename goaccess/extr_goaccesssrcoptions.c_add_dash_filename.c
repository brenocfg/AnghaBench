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
struct TYPE_2__ {int filenames_idx; char** filenames; int read_stdin; } ;

/* Variables and functions */
 int MAX_FILENAMES ; 
 TYPE_1__ conf ; 

void
add_dash_filename (void)
{
  int i;
  // pre-scan for '-' and don't add if already exists: github.com/allinurl/goaccess/issues/907
  for (i = 0; i < conf.filenames_idx; ++i) {
    if (conf.filenames[i][0] == '-' && conf.filenames[i][1] == '\0')
      return;
  }

  if (conf.filenames_idx < MAX_FILENAMES && !conf.read_stdin) {
    conf.read_stdin = 1;
    conf.filenames[conf.filenames_idx++] = "-";
  }
}