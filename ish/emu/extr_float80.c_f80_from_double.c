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
typedef  int uint64_t ;
struct double_bits {scalar_t__ exp; scalar_t__ signif; int /*<<< orphan*/  sign; } ;
struct TYPE_5__ {int signif; int /*<<< orphan*/  sign; void* exp; } ;
typedef  TYPE_1__ float80 ;
typedef  int /*<<< orphan*/  db ;

/* Variables and functions */
 int CURSED_BIT ; 
 scalar_t__ EXP64_DENORMAL ; 
 scalar_t__ EXP64_SPECIAL ; 
 void* EXP_SPECIAL ; 
 void* bias (int) ; 
 TYPE_1__ f80_normalize (TYPE_1__) ; 
 int /*<<< orphan*/  memcpy (struct double_bits*,double*,int) ; 

float80 f80_from_double(double d) {
    struct double_bits db;
    memcpy(&db, &d, sizeof(db));
    float80 f;

    if (db.exp == EXP64_SPECIAL)
        f.exp = EXP_SPECIAL;
    else if (db.exp == EXP64_DENORMAL)
        // denormals actually have an exponent of EXP_MIN, the special exponent
        // is needed to indicate the integer bit is 0
        // zeroes have the same exponent as denormals but need to be handled
        // differently
        f.exp = db.signif == 0 ? 0 : bias(1 - 0x3ff);
    else
        f.exp = bias((int) db.exp - 0x3ff);

    f.signif = (uint64_t) db.signif << 11;
    if (db.exp != EXP64_DENORMAL)
        f.signif |= CURSED_BIT;
    f.sign = db.sign;
    return f80_normalize(f);
}