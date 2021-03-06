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
 int /*<<< orphan*/  INC_REF (void*) ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void *tlsub_push_type_var (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  *(Data ++) = vars[(long)*(IP ++)];
#ifdef VLOG
  fprintf (stderr, "Push type var\n");
#endif
  INC_REF (*(Data - 1));
  TLUNI_NEXT;
}