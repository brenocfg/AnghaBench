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
struct jv_parser {int flags; int stackpos; int /*<<< orphan*/  st; scalar_t__ tokenpos; void** stack; void* next; void* output; int /*<<< orphan*/  last_seen; scalar_t__ stacklen; void* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  JV_LAST_NONE ; 
 int /*<<< orphan*/  JV_PARSER_NORMAL ; 
 int JV_PARSE_STREAMING ; 
 void* jv_array () ; 
 int /*<<< orphan*/  jv_free (void*) ; 
 void* jv_invalid () ; 

__attribute__((used)) static void parser_reset(struct jv_parser* p) {
  if ((p->flags & JV_PARSE_STREAMING)) {
    jv_free(p->path);
    p->path = jv_array();
    p->stacklen = 0;
  }
  p->last_seen = JV_LAST_NONE;
  jv_free(p->output);
  p->output = jv_invalid();
  jv_free(p->next);
  p->next = jv_invalid();
  for (int i=0; i<p->stackpos; i++)
    jv_free(p->stack[i]);
  p->stackpos = 0;
  p->tokenpos = 0;
  p->st = JV_PARSER_NORMAL;
}