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
struct tl_scheme_parse_resource {int /*<<< orphan*/  sb; scalar_t__ stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_scheme_object_free (scalar_t__) ; 
 int /*<<< orphan*/  tl_string_buffer_free (int /*<<< orphan*/ *) ; 

void tl_scheme_parse_cleanup (struct tl_scheme_parse_resource *R) {
  if (R->stack) {
    tl_scheme_object_free (R->stack);
  }
  tl_string_buffer_free (&R->sb);
}