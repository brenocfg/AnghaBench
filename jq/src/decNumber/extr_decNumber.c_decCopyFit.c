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
typedef  int /*<<< orphan*/  uInt ;
struct TYPE_5__ {int /*<<< orphan*/  digits; int /*<<< orphan*/  lsu; int /*<<< orphan*/  exponent; int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ decNumber ;
typedef  int /*<<< orphan*/  decContext ;
typedef  int /*<<< orphan*/  Int ;

/* Variables and functions */
 int /*<<< orphan*/  decSetCoeff (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decCopyFit(decNumber *dest, const decNumber *src,
                       decContext *set, Int *residue, uInt *status) {
  dest->bits=src->bits;
  dest->exponent=src->exponent;
  decSetCoeff(dest, set, src->lsu, src->digits, residue, status);
  }