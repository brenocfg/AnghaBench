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
struct item {int item_id; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct item** Items ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  fsync (int) ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 int /*<<< orphan*/  sort_items () ; 
 int tot_items ; 

void dump_itemids (char *filename) {
  int i;
  FILE *f = fopen (filename, "w");
  if (f == NULL) {
    kprintf ("fopen (\"%s\", \"w\") fail. %m\n", filename);
    exit (1);
  }
  sort_items ();
  for (i = 0; i < tot_items; i++) {
    struct item *I = Items[i];
    int t = (int) (I->item_id >> 32);
    if (t) {
      fprintf (f, "%d_%d\n", (int) I->item_id, t);
    } else {
      fprintf (f, "%d\n", (int) I->item_id);
    }
  }
  int fd = fileno (f);
  assert (fd >= 0);
  assert (!fsync (fd));
  assert (!fclose (f));
}