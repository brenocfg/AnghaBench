#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* literal_data; } ;
typedef  TYPE_1__ jvp_literal_number ;
typedef  int /*<<< orphan*/  jv ;
struct TYPE_10__ {int digits; } ;
typedef  TYPE_2__ decNumber ;

/* Variables and functions */
 char const* DBL_MAX_STR ; 
 char const* DBL_MIN_STR ; 
 int /*<<< orphan*/  JVP_FLAGS_NUMBER_LITERAL ; 
 int /*<<< orphan*/  JVP_HAS_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ decNumberIsInfinite (TYPE_2__*) ; 
 scalar_t__ decNumberIsNaN (TYPE_2__*) ; 
 scalar_t__ decNumberIsNegative (TYPE_2__*) ; 
 int /*<<< orphan*/  decNumberToString (TYPE_2__*,char const*) ; 
 char const* jv_mem_alloc (int) ; 
 TYPE_2__* jvp_dec_number_ptr (int /*<<< orphan*/ ) ; 
 TYPE_1__* jvp_literal_number_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char* jvp_literal_number_literal(jv n) {
  assert(JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL));
  decNumber *pdec = jvp_dec_number_ptr(n);
  jvp_literal_number* plit = jvp_literal_number_ptr(n);

  if (decNumberIsNaN(pdec)) {
    return "null";
  }

  if (decNumberIsInfinite(pdec)) {
    // For backward compatibiltiy.
    if (decNumberIsNegative(pdec)) {
      return DBL_MIN_STR;
    } else {
      return DBL_MAX_STR;
    }
  }

  if (plit->literal_data == NULL) {
    int len = jvp_dec_number_ptr(n)->digits + 14;
    plit->literal_data = jv_mem_alloc(len);

    // Preserve the actual precision as we have parsed it
    // don't do decNumberTrim(pdec);
    
    decNumberToString(pdec, plit->literal_data);
  }

  return plit->literal_data;
}