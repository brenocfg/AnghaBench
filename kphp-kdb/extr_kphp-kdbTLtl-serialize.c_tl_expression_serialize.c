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
struct tl_int_array {int dummy; } ;
struct tl_compiler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_SECTION_FUNCTIONS ; 
 int tl_expression_serialize_general (struct tl_compiler*,struct tl_scheme_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tl_int_array*) ; 

int tl_expression_serialize (struct tl_compiler *C, struct tl_scheme_object *E, struct tl_int_array *a) {
  return tl_expression_serialize_general (C, E, TL_SECTION_FUNCTIONS, NULL, a);
}