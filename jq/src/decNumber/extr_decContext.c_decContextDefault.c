#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int digits; int emax; int emin; int clamp; int extended; int /*<<< orphan*/  traps; void* round; scalar_t__ status; } ;
typedef  TYPE_1__ decContext ;
typedef  int Int ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_Errors ; 
#define  DEC_INIT_BASE 131 
#define  DEC_INIT_DECIMAL128 130 
#define  DEC_INIT_DECIMAL32 129 
#define  DEC_INIT_DECIMAL64 128 
 int /*<<< orphan*/  DEC_Invalid_operation ; 
 int DEC_MAX_EMAX ; 
 int DEC_MIN_EMIN ; 
 void* DEC_ROUND_HALF_EVEN ; 
 void* DEC_ROUND_HALF_UP ; 
 int /*<<< orphan*/  decContextSetStatus (TYPE_1__*,int /*<<< orphan*/ ) ; 

decContext * decContextDefault(decContext *context, Int kind) {
  // set defaults...
  context->digits=9;                         // 9 digits
  context->emax=DEC_MAX_EMAX;                // 9-digit exponents
  context->emin=DEC_MIN_EMIN;                // .. balanced
  context->round=DEC_ROUND_HALF_UP;          // 0.5 rises
  context->traps=DEC_Errors;                 // all but informational
  context->status=0;                         // cleared
  context->clamp=0;                          // no clamping
  #if DECSUBSET
  context->extended=0;                       // cleared
  #endif
  switch (kind) {
    case DEC_INIT_BASE:
      // [use defaults]
      break;
    case DEC_INIT_DECIMAL32:
      context->digits=7;                     // digits
      context->emax=96;                      // Emax
      context->emin=-95;                     // Emin
      context->round=DEC_ROUND_HALF_EVEN;    // 0.5 to nearest even
      context->traps=0;                      // no traps set
      context->clamp=1;                      // clamp exponents
      #if DECSUBSET
      context->extended=1;                   // set
      #endif
      break;
    case DEC_INIT_DECIMAL64:
      context->digits=16;                    // digits
      context->emax=384;                     // Emax
      context->emin=-383;                    // Emin
      context->round=DEC_ROUND_HALF_EVEN;    // 0.5 to nearest even
      context->traps=0;                      // no traps set
      context->clamp=1;                      // clamp exponents
      #if DECSUBSET
      context->extended=1;                   // set
      #endif
      break;
    case DEC_INIT_DECIMAL128:
      context->digits=34;                    // digits
      context->emax=6144;                    // Emax
      context->emin=-6143;                   // Emin
      context->round=DEC_ROUND_HALF_EVEN;    // 0.5 to nearest even
      context->traps=0;                      // no traps set
      context->clamp=1;                      // clamp exponents
      #if DECSUBSET
      context->extended=1;                   // set
      #endif
      break;

    default:                                 // invalid Kind
      // use defaults, and ..
      decContextSetStatus(context, DEC_Invalid_operation); // trap
    }

  return context;}