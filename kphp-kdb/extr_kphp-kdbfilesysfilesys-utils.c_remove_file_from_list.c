#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ file_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_file (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char const* const,int /*<<< orphan*/ ) ; 

file_t *remove_file_from_list (file_t *x, const char *const filename) {
  int t = 0;
  file_t **p = &x;
  while (*p != NULL) {
    file_t *V = *p;
    assert (V->filename);
    if (!strcmp (filename, V->filename)) {
      *p = V->next;
      free_file (V);
      return t ? x : *p;
    }
    p = &V->next;
    t++;
  }
  return x;
}