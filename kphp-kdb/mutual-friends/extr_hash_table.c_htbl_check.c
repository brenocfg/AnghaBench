#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int hash; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ hash_table ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int poly_h (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

inline void htbl_check (hash_table *table) {
  int need = poly_h (table->h, table->size);
  if (need != table->hash) {
    fprintf (stderr, "Wrong hashtable: size = %d, h = %p.", table->size, table->h);
    fflush (stderr);
  }
  assert (need == table->hash);
}