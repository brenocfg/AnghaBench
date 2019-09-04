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
struct TYPE_2__ {int ignore_referer_idx; char** ignore_referers; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ wc_match (char*,char*) ; 
 char* xstrdup (char const*) ; 

int
ignore_referer (const char *host)
{
  char *needle = NULL;
  int i, ignore = 0;

  if (conf.ignore_referer_idx == 0)
    return 0;
  if (host == NULL || *host == '\0')
    return 0;

  needle = xstrdup (host);
  for (i = 0; i < conf.ignore_referer_idx; ++i) {
    if (conf.ignore_referers[i] == NULL || *conf.ignore_referers[i] == '\0')
      continue;

    if (wc_match (conf.ignore_referers[i], needle)) {
      ignore = 1;
      goto out;
    }
  }
out:
  free (needle);

  return ignore;
}