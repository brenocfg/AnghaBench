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
typedef  int list_id_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 

void dump_list_id(FILE *f, list_id_t list_id) {
#ifdef	LISTS_Z 
  fprintf(f, "%s", out_list_id(list_id));  
#elif defined(LISTS64)
  fprintf(f, "%lld", list_id)  
#else
  fprintf(f, "%d", list_id);
#endif  
}