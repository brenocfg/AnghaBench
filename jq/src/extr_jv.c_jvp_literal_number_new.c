#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  num_double; int /*<<< orphan*/  num_decimal; int /*<<< orphan*/ * literal_data; } ;
typedef  TYPE_2__ jvp_literal_number ;
struct TYPE_11__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_13__ {TYPE_1__ member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ jv ;
struct TYPE_14__ {int status; } ;
typedef  TYPE_4__ decContext ;

/* Variables and functions */
 TYPE_4__* DEC_CONTEXT () ; 
 int DEC_Conversion_syntax ; 
 int /*<<< orphan*/  JVP_FLAGS_NUMBER_LITERAL ; 
 TYPE_3__ JV_INVALID ; 
 int /*<<< orphan*/  JV_NUMBER_SIZE_INIT ; 
 int /*<<< orphan*/  JV_REFCNT_INIT ; 
 int /*<<< orphan*/  NAN ; 
 int /*<<< orphan*/  decNumberFromString (int /*<<< orphan*/ *,char const*,TYPE_4__*) ; 
 int /*<<< orphan*/  jv_mem_free (TYPE_2__*) ; 
 TYPE_2__* jvp_literal_number_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static jv jvp_literal_number_new(const char * literal) {

  jvp_literal_number * n = jvp_literal_number_alloc(strlen(literal));

  n->refcnt = JV_REFCNT_INIT;
  n->literal_data = NULL;
  decContext *ctx = DEC_CONTEXT();
  decNumberFromString(&n->num_decimal, literal, ctx);
  n->num_double = NAN;

  if (ctx->status & DEC_Conversion_syntax) {
    jv_mem_free(n);
    return JV_INVALID;
  }

  jv r = {JVP_FLAGS_NUMBER_LITERAL, 0, 0, JV_NUMBER_SIZE_INIT, {&n->refcnt}};
  return r;
}