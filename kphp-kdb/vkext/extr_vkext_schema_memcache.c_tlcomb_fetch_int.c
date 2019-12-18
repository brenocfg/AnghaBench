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
typedef  int /*<<< orphan*/  zval ;
struct tl_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_STD_ZVAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* tl_parse_error () ; 
 int tl_parse_int () ; 

void *tlcomb_fetch_int (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  int a = tl_parse_int ();
#ifdef VLOG
  fprintf (stderr, "!!!%d (0x%08x). error %s\n", a, a, tl_parse_error () ? tl_parse_error () : "none");
#endif
  if (tl_parse_error ()) { return 0; }
  MAKE_STD_ZVAL (*arr);
  ZVAL_LONG (*arr, a);
  TLUNI_NEXT;
}