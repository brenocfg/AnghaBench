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
struct cword {int num; int c; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TL ; 
 scalar_t__ TS ; 
 int Tc ; 
 scalar_t__ Tw ; 
 int /*<<< orphan*/  asort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 
 struct cword* write_alloc (int) ; 

__attribute__((used)) static void flush_words (void) {
  int i, j, len;
  struct cword *W;
  if (!Tc) { return; }
  if (verbosity > 0) {
    fprintf (stderr, "sorting words: %d words, %ld chars\n", Tc, (long)(Tw - TS));
  }
  asort (0, Tc-1);
  i = 0;
  while (i < Tc) {
    j = i+1;
    len = strlen (TL[i]);
    while (j < Tc && !strcmp (TL[i], TL[j])) { j++; }
    W = write_alloc (6 + len);
    W->num = j - i;
    W->c = len;
    memcpy (W->s, TL[i], len+1);
    i = j;
  }
  W = write_alloc (4);
  W->num = -1;
  Tc = 0;
  Tw = TS;
}