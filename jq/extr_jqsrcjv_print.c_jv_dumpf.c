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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  jv_dump_term (struct dtoa_context*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_dtoa_context_free (struct dtoa_context*) ; 
 int /*<<< orphan*/  jvp_dtoa_context_init (struct dtoa_context*) ; 

void jv_dumpf(jv x, FILE *f, int flags) {
  struct dtoa_context C;
  jvp_dtoa_context_init(&C);
  jv_dump_term(&C, x, flags, 0, f, 0);
  jvp_dtoa_context_free(&C);
}