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
struct jv_parser {int flags; } ;

/* Variables and functions */
 struct jv_parser* jv_mem_alloc (int) ; 
 int /*<<< orphan*/  parser_init (struct jv_parser*,int) ; 

struct jv_parser* jv_parser_new(int flags) {
  struct jv_parser* p = jv_mem_alloc(sizeof(struct jv_parser));
  parser_init(p, flags);
  p->flags = flags;
  return p;
}