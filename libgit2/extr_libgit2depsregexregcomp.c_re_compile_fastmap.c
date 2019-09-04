#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct re_pattern_buffer {char* fastmap; int fastmap_accurate; scalar_t__ buffer; } ;
struct TYPE_2__ {scalar_t__ init_state; scalar_t__ init_state_word; scalar_t__ init_state_nl; scalar_t__ init_state_begbuf; } ;
typedef  TYPE_1__ re_dfa_t ;

/* Variables and functions */
 int SBC_MAX ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  re_compile_fastmap_iter (struct re_pattern_buffer*,scalar_t__,char*) ; 

int
re_compile_fastmap (struct re_pattern_buffer *bufp)
{
  re_dfa_t *dfa = (re_dfa_t *) bufp->buffer;
  char *fastmap = bufp->fastmap;

  memset (fastmap, '\0', sizeof (char) * SBC_MAX);
  re_compile_fastmap_iter (bufp, dfa->init_state, fastmap);
  if (dfa->init_state != dfa->init_state_word)
    re_compile_fastmap_iter (bufp, dfa->init_state_word, fastmap);
  if (dfa->init_state != dfa->init_state_nl)
    re_compile_fastmap_iter (bufp, dfa->init_state_nl, fastmap);
  if (dfa->init_state != dfa->init_state_begbuf)
    re_compile_fastmap_iter (bufp, dfa->init_state_begbuf, fastmap);
  bufp->fastmap_accurate = 1;
  return 0;
}