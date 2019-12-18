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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static void
append_query_string (char **req, const char *qstr)
{
  char *r;
  size_t s1, s2, qm = 0;

  s1 = strlen (*req);
  s2 = strlen (qstr);

  /* add '?' between the URL and the query string */
  if (*qstr != '?')
    qm = 1;

  r = xmalloc (s1 + s2 + qm + 1);
  memcpy (r, *req, s1);
  if (qm)
    r[s1] = '?';
  memcpy (r + s1 + qm, qstr, s2 + 1);

  free (*req);
  *req = r;
}