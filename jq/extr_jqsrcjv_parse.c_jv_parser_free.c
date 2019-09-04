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
struct jv_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jv_mem_free (struct jv_parser*) ; 
 int /*<<< orphan*/  parser_free (struct jv_parser*) ; 

void jv_parser_free(struct jv_parser* p) {
  parser_free(p);
  jv_mem_free(p);
}