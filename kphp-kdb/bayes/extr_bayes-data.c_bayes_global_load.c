#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  entry_t ;
struct TYPE_7__ {int n; int size; TYPE_1__* e; } ;
struct TYPE_6__ {TYPE_3__ cnt; } ;
typedef  TYPE_1__ bayes ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int max_words ; 
 int /*<<< orphan*/  qhtbl_init (TYPE_3__*) ; 
 int /*<<< orphan*/  qhtbl_set_size (TYPE_3__*,int) ; 
 int read (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 

void bayes_global_load (bayes *global_bayes) {
  int size = 3 * sizeof (int) + 2 * sizeof (long long);
  int r = read (fd[0], global_bayes, size);
  if (r != size) {
    fprintf (stderr, "error reading header from index file: read %d bytes instead of %d at position ???: %m\n", r, size);
    assert (r == size);
  }

  int new_n = global_bayes->cnt.n,
      new_size = global_bayes->cnt.size;
  if (new_size > max_words) {
    max_words = new_size;
  }

  qhtbl_init (&global_bayes->cnt);
  qhtbl_set_size (&global_bayes->cnt, new_n);
  global_bayes->cnt.size = new_size;

  size = sizeof (entry_t) * new_n;
  r = read (fd[0], global_bayes->cnt.e, size);
  if (r != size) {
    fprintf (stderr, "error reading header from index file: read %d bytes instead of %d at position ???: %m\n", r, size);
    assert (r == size);
  }
}