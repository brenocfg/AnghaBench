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
struct tl_buffer {scalar_t__ size; int pos; int /*<<< orphan*/  buff; } ;

/* Variables and functions */
 char* cstr_dup (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* tl_zzmalloc (int) ; 

char *tl_string_buffer_to_cstr (struct tl_buffer *b) {
  if (b->size == 0) {
    return cstr_dup ("");
  }
  char *s = tl_zzmalloc (b->pos+1);
  memcpy (s, b->buff, b->pos);
  s[b->pos] = 0;
  return s;
}