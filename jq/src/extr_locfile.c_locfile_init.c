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
struct locfile {int length; int nlines; int refct; int* linemap; void* data; int /*<<< orphan*/  fname; int /*<<< orphan*/ * jq; } ;
typedef  int /*<<< orphan*/  jq_state ;

/* Variables and functions */
 void* jv_mem_alloc (int) ; 
 int* jv_mem_calloc (int,int) ; 
 int /*<<< orphan*/  jv_string (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

struct locfile* locfile_init(jq_state *jq, const char *fname, const char* data, int length) {
  struct locfile* l = jv_mem_alloc(sizeof(struct locfile));
  l->jq = jq;
  l->fname = jv_string(fname);
  l->data = jv_mem_alloc(length);
  memcpy((char*)l->data,data,length);
  l->length = length;
  l->nlines = 1;
  l->refct = 1;
  for (int i=0; i<length; i++) {
    if (data[i] == '\n') l->nlines++;
  }
  l->linemap = jv_mem_calloc(sizeof(int), (l->nlines + 1));
  l->linemap[0] = 0;
  int line = 1;
  for (int i=0; i<length; i++) {
    if (data[i] == '\n') {
      l->linemap[line] = i+1;   // at start of line, not of \n
      line++;
    }
  }
  l->linemap[l->nlines] = length+1;   // virtual last \n
  return l;
}