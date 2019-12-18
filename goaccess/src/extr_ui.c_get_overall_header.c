#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ idx; } ;
typedef  TYPE_1__ GHolder ;

/* Variables and functions */
 char* T_DASH_HEAD ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_start_end_parsing_dates (TYPE_1__*,char**,char**,char*) ; 
 scalar_t__ snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*,char*) ; 
 char* xmalloc (scalar_t__) ; 
 char* xstrdup (char const*) ; 

char *
get_overall_header (GHolder * h)
{
  const char *head = T_DASH_HEAD;
  char *hd = NULL, *start = NULL, *end = NULL;

  if (h->idx == 0 || get_start_end_parsing_dates (h, &start, &end, "%d/%b/%Y"))
    return xstrdup (head);

  hd = xmalloc (snprintf (NULL, 0, "%s (%s - %s)", head, start, end) + 1);
  sprintf (hd, "%s (%s - %s)", head, start, end);

  free (end);
  free (start);

  return hd;
}