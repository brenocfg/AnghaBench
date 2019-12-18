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
struct tl_scheme_object {int dummy; } ;
struct tl_buffer {char* buff; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  tl_scheme_object_sbdump (struct tl_buffer*,struct tl_scheme_object*) ; 
 int /*<<< orphan*/  tl_string_buffer_append_char (struct tl_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_string_buffer_free (struct tl_buffer*) ; 
 int /*<<< orphan*/  tl_string_buffer_init (struct tl_buffer*) ; 

void tl_scheme_object_dump (FILE *f, struct tl_scheme_object *O) {
  struct tl_buffer b;
  tl_string_buffer_init (&b);
  tl_scheme_object_sbdump (&b, O);
  tl_string_buffer_append_char (&b, 0);
  fprintf (f, "%s", b.buff);
  tl_string_buffer_free (&b);
}