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
struct jv_parser {int tokenpos; int tokenlen; char* tokenbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* jv_mem_realloc (char*,int) ; 

__attribute__((used)) static void tokenadd(struct jv_parser* p, char c) {
  assert(p->tokenpos <= p->tokenlen);
  if (p->tokenpos >= (p->tokenlen - 1)) {
    p->tokenlen = p->tokenlen*2 + 256;
    p->tokenbuf = jv_mem_realloc(p->tokenbuf, p->tokenlen);
  }
  assert(p->tokenpos < p->tokenlen);
  p->tokenbuf[p->tokenpos++] = c;
}