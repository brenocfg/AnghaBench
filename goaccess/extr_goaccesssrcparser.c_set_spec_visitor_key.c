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
struct TYPE_2__ {scalar_t__ date_spec_hr; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 char* xmalloc (size_t) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
set_spec_visitor_key (char **fdate, const char *ftime)
{
  size_t dlen = 0, tlen = 0;
  char *key = NULL, *tkey = NULL, *pch = NULL;

  tkey = xstrdup (ftime);
  if (conf.date_spec_hr && (pch = strchr (tkey, ':')) && (pch - tkey) > 0)
    *pch = '\0';

  dlen = strlen (*fdate);
  tlen = strlen (tkey);

  key = xmalloc (dlen + tlen + 1);
  memcpy (key, *fdate, dlen);
  memcpy (key + dlen, tkey, tlen + 1);

  free (*fdate);
  free (tkey);
  *fdate = key;
}