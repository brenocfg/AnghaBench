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
typedef  int /*<<< orphan*/  jv ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ decNumberDoublePrecision ;
typedef  int /*<<< orphan*/  decNumber ;

/* Variables and functions */
 scalar_t__ BIN64_DEC_PRECISION ; 
 int /*<<< orphan*/  DEC_CONTEXT_TO_DOUBLE () ; 
 scalar_t__ DEC_NUMBER_STRING_GUARD ; 
 int /*<<< orphan*/  JVP_FLAGS_NUMBER_LITERAL ; 
 int /*<<< orphan*/  JVP_HAS_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decNumberReduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decNumberToString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * jvp_dec_number_ptr (int /*<<< orphan*/ ) ; 
 double jvp_strtod (int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  tsd_dtoa_context_get () ; 

__attribute__((used)) static double jvp_literal_number_to_double(jv j) {
  assert(JVP_HAS_FLAGS(j, JVP_FLAGS_NUMBER_LITERAL));

  decNumber *p_dec_number = jvp_dec_number_ptr(j);
  decNumberDoublePrecision dec_double;
  char literal[BIN64_DEC_PRECISION + DEC_NUMBER_STRING_GUARD + 1]; 

  // reduce the number to the shortest possible form
  // while also making sure than no more than BIN64_DEC_PRECISION 
  // digits are used (dec_context_to_double)
  decNumberReduce(&dec_double.number, p_dec_number, DEC_CONTEXT_TO_DOUBLE());

  decNumberToString(&dec_double.number, literal);

  char *end;
  return jvp_strtod(tsd_dtoa_context_get(), literal, &end);
}