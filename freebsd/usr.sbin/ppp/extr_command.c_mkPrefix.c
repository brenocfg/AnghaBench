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
 int strlen (char const* const) ; 
 int /*<<< orphan*/  strncpy (char*,char const* const,int) ; 

__attribute__((used)) static const char *
mkPrefix(int argc, char const *const *argv, char *tgt, int sz)
{
  int f, tlen, len;

  tlen = 0;
  for (f = 0; f < argc && tlen < sz - 2; f++) {
    if (f)
      tgt[tlen++] = ' ';
    len = strlen(argv[f]);
    if (len > sz - tlen - 1)
      len = sz - tlen - 1;
    strncpy(tgt+tlen, argv[f], len);
    tlen += len;
  }
  tgt[tlen] = '\0';
  return tgt;
}