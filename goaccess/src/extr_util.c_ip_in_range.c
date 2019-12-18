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
struct TYPE_2__ {int ignore_ip_idx; char** ignore_ips; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ within_range (char const*,char*,char*) ; 
 char* xstrdup (char*) ; 

int
ip_in_range (const char *ip)
{
  char *start = NULL, *end, *dash;
  int i;

  for (i = 0; i < conf.ignore_ip_idx; ++i) {
    end = NULL;
    if (conf.ignore_ips[i] == NULL || *conf.ignore_ips[i] == '\0')
      continue;

    start = xstrdup (conf.ignore_ips[i]);
    /* split range */
    if ((dash = strchr (start, '-')) != NULL) {
      *dash = '\0';
      end = dash + 1;
    }

    /* matches single IP */
    if (end == NULL && start) {
      if (strcmp (ip, start) == 0) {
        free (start);
        return 1;
      }
    }
    /* within range */
    else if (start && end) {
      if (within_range (ip, start, end)) {
        free (start);
        return 1;
      }
    }
    free (start);
  }

  return 0;
}