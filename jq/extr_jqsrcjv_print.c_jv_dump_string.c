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
struct dtoa_context {int dummy; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  jv_dump_term (struct dtoa_context*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jvp_dtoa_context_free (struct dtoa_context*) ; 
 int /*<<< orphan*/  jvp_dtoa_context_init (struct dtoa_context*) ; 

jv jv_dump_string(jv x, int flags) {
  struct dtoa_context C;
  jvp_dtoa_context_init(&C);
  jv s = jv_string("");
  jv_dump_term(&C, x, flags, 0, 0, &s);
  jvp_dtoa_context_free(&C);
  return s;
}