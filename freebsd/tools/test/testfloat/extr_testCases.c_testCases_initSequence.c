#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8 ;
struct TYPE_12__ {void* done; scalar_t__ expNum; scalar_t__ term1Num; scalar_t__ term2Num; } ;
struct TYPE_11__ {void* done; scalar_t__ expNum; scalar_t__ term1Num; scalar_t__ term2Num; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  current_a_float128 ; 
 int /*<<< orphan*/  current_a_float32 ; 
 int /*<<< orphan*/  current_a_float64 ; 
 int /*<<< orphan*/  current_a_floatx80 ; 
 int /*<<< orphan*/  float128NextQInP1 (TYPE_2__*) ; 
 int /*<<< orphan*/  float128NextQInP2 (TYPE_2__*) ; 
 int float128NumQInP1 ; 
 int float128NumQInP2 ; 
 int float128NumQOutP1 ; 
 int float128NumQOutP2 ; 
 int /*<<< orphan*/  float32NextQInP1 (TYPE_2__*) ; 
 int /*<<< orphan*/  float32NextQInP2 (TYPE_2__*) ; 
 int float32NumQInP1 ; 
 int float32NumQInP2 ; 
 int float32NumQOutP1 ; 
 int float32NumQOutP2 ; 
 int /*<<< orphan*/  float64NextQInP1 (TYPE_2__*) ; 
 int /*<<< orphan*/  float64NextQInP2 (TYPE_2__*) ; 
 int float64NumQInP1 ; 
 int float64NumQInP2 ; 
 int float64NumQOutP1 ; 
 int float64NumQOutP2 ; 
 int /*<<< orphan*/  floatx80NextQInP1 (TYPE_2__*) ; 
 int /*<<< orphan*/  floatx80NextQInP2 (TYPE_2__*) ; 
 int floatx80NumQInP1 ; 
 int floatx80NumQInP2 ; 
 int floatx80NumQOutP1 ; 
 int floatx80NumQOutP2 ; 
 int int32NumP1 ; 
 int int32NumP2 ; 
 int int64NumP1 ; 
 int int64NumP2 ; 
 int level ; 
 TYPE_2__ sequenceA ; 
 TYPE_1__ sequenceB ; 
 int /*<<< orphan*/  sequenceType ; 
 scalar_t__ subcase ; 
 void* testCases_done ; 
#define  testCases_sequence_a_float128 137 
#define  testCases_sequence_a_float32 136 
#define  testCases_sequence_a_float64 135 
#define  testCases_sequence_a_floatx80 134 
#define  testCases_sequence_a_int32 133 
#define  testCases_sequence_a_int64 132 
#define  testCases_sequence_ab_float128 131 
#define  testCases_sequence_ab_float32 130 
#define  testCases_sequence_ab_float64 129 
#define  testCases_sequence_ab_floatx80 128 
 int testCases_total ; 

void testCases_initSequence( int8 sequenceTypeIn )
{

    sequenceType = sequenceTypeIn;
    sequenceA.term2Num = 0;
    sequenceA.term1Num = 0;
    sequenceA.expNum = 0;
    sequenceA.done = FALSE;
    sequenceB.term2Num = 0;
    sequenceB.term1Num = 0;
    sequenceB.expNum = 0;
    sequenceB.done = FALSE;
    subcase = 0;
    switch ( level ) {
     case 1:
        switch ( sequenceTypeIn ) {
         case testCases_sequence_a_int32:
            testCases_total = 3 * int32NumP1;
            break;
#ifdef BITS64
         case testCases_sequence_a_int64:
            testCases_total = 3 * int64NumP1;
            break;
#endif
         case testCases_sequence_a_float32:
            testCases_total = 3 * float32NumQOutP1;
            break;
         case testCases_sequence_ab_float32:
            testCases_total = 6 * float32NumQInP1 * float32NumQInP1;
            current_a_float32 = float32NextQInP1( &sequenceA );
            break;
         case testCases_sequence_a_float64:
            testCases_total = 3 * float64NumQOutP1;
            break;
         case testCases_sequence_ab_float64:
            testCases_total = 6 * float64NumQInP1 * float64NumQInP1;
            current_a_float64 = float64NextQInP1( &sequenceA );
            break;
#ifdef FLOATX80
         case testCases_sequence_a_floatx80:
            testCases_total = 3 * floatx80NumQOutP1;
            break;
         case testCases_sequence_ab_floatx80:
            testCases_total = 6 * floatx80NumQInP1 * floatx80NumQInP1;
            current_a_floatx80 = floatx80NextQInP1( &sequenceA );
            break;
#endif
#ifdef FLOAT128
         case testCases_sequence_a_float128:
            testCases_total = 3 * float128NumQOutP1;
            break;
         case testCases_sequence_ab_float128:
            testCases_total = 6 * float128NumQInP1 * float128NumQInP1;
            current_a_float128 = float128NextQInP1( &sequenceA );
            break;
#endif
        }
        break;
     case 2:
        switch ( sequenceTypeIn ) {
         case testCases_sequence_a_int32:
            testCases_total = 2 * int32NumP2;
            break;
#ifdef BITS64
         case testCases_sequence_a_int64:
            testCases_total = 2 * int64NumP2;
            break;
#endif
         case testCases_sequence_a_float32:
            testCases_total = 2 * float32NumQOutP2;
            break;
         case testCases_sequence_ab_float32:
            testCases_total = 2 * float32NumQInP2 * float32NumQInP2;
            current_a_float32 = float32NextQInP2( &sequenceA );
            break;
         case testCases_sequence_a_float64:
            testCases_total = 2 * float64NumQOutP2;
            break;
         case testCases_sequence_ab_float64:
            testCases_total = 2 * float64NumQInP2 * float64NumQInP2;
            current_a_float64 = float64NextQInP2( &sequenceA );
            break;
#ifdef FLOATX80
         case testCases_sequence_a_floatx80:
            testCases_total = 2 * floatx80NumQOutP2;
            break;
         case testCases_sequence_ab_floatx80:
            testCases_total = 2 * floatx80NumQInP2 * floatx80NumQInP2;
            current_a_floatx80 = floatx80NextQInP2( &sequenceA );
            break;
#endif
#ifdef FLOAT128
         case testCases_sequence_a_float128:
            testCases_total = 2 * float128NumQOutP2;
            break;
         case testCases_sequence_ab_float128:
            testCases_total = 2 * float128NumQInP2 * float128NumQInP2;
            current_a_float128 = float128NextQInP2( &sequenceA );
            break;
#endif
        }
        break;
    }
    testCases_done = FALSE;

}