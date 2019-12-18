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
struct TYPE_2__ {int hide_referer_idx; char** hide_referers; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ wc_match (char*,char*) ; 
 char* xstrdup (char const*) ; 

int
hide_referer (const char *host)
{
  char *needle = NULL;
  int i, ignore = 0;

  if (conf.hide_referer_idx == 0)
    return 0;
  if (host == NULL || *host == '\0')
    return 0;

  needle = xstrdup (host);
  for (i = 0; i < conf.hide_referer_idx; ++i) {
    if (conf.hide_referers[i] == NULL || *conf.hide_referers[i] == '\0')
      continue;

    if (wc_match (conf.hide_referers[i], needle)) {
      ignore = 1;
      goto out;
    }
  }
out:
  free (needle);

  return ignore;
}