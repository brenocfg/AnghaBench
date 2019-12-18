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
struct tl_buffer {int size; int /*<<< orphan*/  buff; scalar_t__ pos; } ;

/* Variables and functions */
 int TL_STRING_BUFFER_MIN_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

__attribute__((used)) static void tl_string_buffer_extend (struct tl_buffer *b) {
  if (verbosity >= 4) {
    fprintf (stderr, "tl_string_buffer_extend: b->size (%d)\n", b->size);
  }
  if (b->size == 0) {
    b->size = TL_STRING_BUFFER_MIN_SIZE;
    b->buff = malloc (b->size);
    b->pos = 0;
    return;
  }
  b->size *= 2;
  b->buff = realloc (b->buff, b->size);
  assert (b->buff);
}