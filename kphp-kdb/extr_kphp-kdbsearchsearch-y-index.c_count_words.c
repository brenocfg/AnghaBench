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
typedef  scalar_t__ hash_t ;
struct TYPE_2__ {scalar_t__ word; } ;

/* Variables and functions */
 TYPE_1__* P ; 
 int PC ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int count_words (void) {
  int c, m, e, i;
  hash_t word;

  if (!PC) {
    return 0;
  }

  word = P[0].word;
  c = 1;
  m = 0;
  e = 0;
  for (i = 1; i < PC; i++) {
    if (word != P[i].word) {
      word = P[i].word;
      if (!m) { e++; }
      m = 0;
      c++;
    } else {
      m++;
    }
  }

  if (!m) { e++; }

  //hapax_legomena = e;
  if (verbosity > 0) {
    fprintf (stderr, "%d distinct words, %d hapax legomena\n", c, e);
  }
  return c;
  //return c - hapax_legomena;
}