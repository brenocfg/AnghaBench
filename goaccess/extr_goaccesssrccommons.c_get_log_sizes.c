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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_2__ {scalar_t__ log_size; int filenames_idx; char** filenames; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 scalar_t__ file_size (char*) ; 

intmax_t
get_log_sizes (void)
{
  int i;
  off_t size = 0;

  /* --log-size */
  if (conf.log_size > 0)
    return (intmax_t) conf.log_size;

  for (i = 0; i < conf.filenames_idx; ++i) {
    if (conf.filenames[i][0] == '-' && conf.filenames[i][1] == '\0')
      size += 0;
    else
      size += file_size (conf.filenames[i]);
  }

  return (intmax_t) size;
}