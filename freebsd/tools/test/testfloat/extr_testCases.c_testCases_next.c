#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int done; } ;

/* Variables and functions */
 void* FALSE ; 
 void* current_a_float128 ; 
 void* current_a_float32 ; 
 void* current_a_float64 ; 
 void* current_a_floatx80 ; 
 void* current_b_float128 ; 
 void* current_b_float32 ; 
 void* current_b_float64 ; 
 void* current_b_floatx80 ; 
 void* float128NextQInP1 (TYPE_1__*) ; 
 void* float128NextQInP2 (TYPE_1__*) ; 
 void* float128NextQOutP1 (TYPE_1__*) ; 
 void* float128NextQOutP2 (TYPE_1__*) ; 
 void* float128Random () ; 
 void* float32NextQInP1 (TYPE_1__*) ; 
 void* float32NextQInP2 (TYPE_1__*) ; 
 void* float32NextQOutP1 (TYPE_1__*) ; 
 void* float32NextQOutP2 (TYPE_1__*) ; 
 void* float32Random () ; 
 void* float64NextQInP1 (TYPE_1__*) ; 
 void* float64NextQInP2 (TYPE_1__*) ; 
 void* float64NextQOutP1 (TYPE_1__*) ; 
 void* float64NextQOutP2 (TYPE_1__*) ; 
 void* float64Random () ; 
 void* floatx80NextQInP1 (TYPE_1__*) ; 
 void* floatx80NextQInP2 (TYPE_1__*) ; 
 void* floatx80NextQOutP1 (TYPE_1__*) ; 
 void* floatx80NextQOutP2 (TYPE_1__*) ; 
 void* floatx80Random () ; 
 int /*<<< orphan*/  int32NextP1 (TYPE_1__*) ; 
 int /*<<< orphan*/  int32NextP2 (TYPE_1__*) ; 
 int /*<<< orphan*/  int32RandomP3 () ; 
 int /*<<< orphan*/  int32RandomPInf () ; 
 int /*<<< orphan*/  int64NextP1 (TYPE_1__*) ; 
 int /*<<< orphan*/  int64NextP2 (TYPE_1__*) ; 
 int /*<<< orphan*/  int64RandomP3 () ; 
 int /*<<< orphan*/  int64RandomPInf () ; 
 int level ; 
 TYPE_1__ sequenceA ; 
 TYPE_1__ sequenceB ; 
 int /*<<< orphan*/  sequenceType ; 
 int subcase ; 
 void* testCases_a_float128 ; 
 void* testCases_a_float32 ; 
 void* testCases_a_float64 ; 
 void* testCases_a_floatx80 ; 
 int /*<<< orphan*/  testCases_a_int32 ; 
 int /*<<< orphan*/  testCases_a_int64 ; 
 void* testCases_b_float128 ; 
 void* testCases_b_float32 ; 
 void* testCases_b_float64 ; 
 void* testCases_b_floatx80 ; 
 int testCases_done ; 
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

void testCases_next( void )
{

    switch ( level ) {
     case 1:
        switch ( sequenceType ) {
         case testCases_sequence_a_int32:
            switch ( subcase ) {
             case 0:
                testCases_a_int32 = int32RandomP3();
                break;
             case 1:
                testCases_a_int32 = int32RandomPInf();
                break;
             case 2:
                testCases_a_int32 = int32NextP1( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
#ifdef BITS64
         case testCases_sequence_a_int64:
            switch ( subcase ) {
             case 0:
                testCases_a_int64 = int64RandomP3();
                break;
             case 1:
                testCases_a_int64 = int64RandomPInf();
                break;
             case 2:
                testCases_a_int64 = int64NextP1( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
#endif
         case testCases_sequence_a_float32:
            switch ( subcase ) {
             case 0:
             case 1:
                testCases_a_float32 = float32Random();
                break;
             case 2:
                testCases_a_float32 = float32NextQOutP1( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_ab_float32:
            switch ( subcase ) {
             case 0:
                if ( sequenceB.done ) {
                    sequenceB.done = FALSE;
                    current_a_float32 = float32NextQInP1( &sequenceA );
                }
                current_b_float32 = float32NextQInP1( &sequenceB );
             case 2:
             case 4:
                testCases_a_float32 = float32Random();
                testCases_b_float32 = float32Random();
                break;
             case 1:
                testCases_a_float32 = current_a_float32;
                testCases_b_float32 = float32Random();
                break;
             case 3:
                testCases_a_float32 = float32Random();
                testCases_b_float32 = current_b_float32;
                break;
             case 5:
                testCases_a_float32 = current_a_float32;
                testCases_b_float32 = current_b_float32;
                testCases_done = sequenceA.done & sequenceB.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_a_float64:
            switch ( subcase ) {
             case 0:
             case 1:
                testCases_a_float64 = float64Random();
                break;
             case 2:
                testCases_a_float64 = float64NextQOutP1( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_ab_float64:
            switch ( subcase ) {
             case 0:
                if ( sequenceB.done ) {
                    sequenceB.done = FALSE;
                    current_a_float64 = float64NextQInP1( &sequenceA );
                }
                current_b_float64 = float64NextQInP1( &sequenceB );
             case 2:
             case 4:
                testCases_a_float64 = float64Random();
                testCases_b_float64 = float64Random();
                break;
             case 1:
                testCases_a_float64 = current_a_float64;
                testCases_b_float64 = float64Random();
                break;
             case 3:
                testCases_a_float64 = float64Random();
                testCases_b_float64 = current_b_float64;
                break;
             case 5:
                testCases_a_float64 = current_a_float64;
                testCases_b_float64 = current_b_float64;
                testCases_done = sequenceA.done & sequenceB.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
#ifdef FLOATX80
         case testCases_sequence_a_floatx80:
            switch ( subcase ) {
             case 0:
             case 1:
                testCases_a_floatx80 = floatx80Random();
                break;
             case 2:
                testCases_a_floatx80 = floatx80NextQOutP1( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_ab_floatx80:
            switch ( subcase ) {
             case 0:
                if ( sequenceB.done ) {
                    sequenceB.done = FALSE;
                    current_a_floatx80 = floatx80NextQInP1( &sequenceA );
                }
                current_b_floatx80 = floatx80NextQInP1( &sequenceB );
             case 2:
             case 4:
                testCases_a_floatx80 = floatx80Random();
                testCases_b_floatx80 = floatx80Random();
                break;
             case 1:
                testCases_a_floatx80 = current_a_floatx80;
                testCases_b_floatx80 = floatx80Random();
                break;
             case 3:
                testCases_a_floatx80 = floatx80Random();
                testCases_b_floatx80 = current_b_floatx80;
                break;
             case 5:
                testCases_a_floatx80 = current_a_floatx80;
                testCases_b_floatx80 = current_b_floatx80;
                testCases_done = sequenceA.done & sequenceB.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
#endif
#ifdef FLOAT128
         case testCases_sequence_a_float128:
            switch ( subcase ) {
             case 0:
             case 1:
                testCases_a_float128 = float128Random();
                break;
             case 2:
                testCases_a_float128 = float128NextQOutP1( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_ab_float128:
            switch ( subcase ) {
             case 0:
                if ( sequenceB.done ) {
                    sequenceB.done = FALSE;
                    current_a_float128 = float128NextQInP1( &sequenceA );
                }
                current_b_float128 = float128NextQInP1( &sequenceB );
             case 2:
             case 4:
                testCases_a_float128 = float128Random();
                testCases_b_float128 = float128Random();
                break;
             case 1:
                testCases_a_float128 = current_a_float128;
                testCases_b_float128 = float128Random();
                break;
             case 3:
                testCases_a_float128 = float128Random();
                testCases_b_float128 = current_b_float128;
                break;
             case 5:
                testCases_a_float128 = current_a_float128;
                testCases_b_float128 = current_b_float128;
                testCases_done = sequenceA.done & sequenceB.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
#endif
        }
        break;
     case 2:
        switch ( sequenceType ) {
         case testCases_sequence_a_int32:
            switch ( subcase ) {
             case 0:
                testCases_a_int32 = int32RandomP3();
                break;
             case 2:
                testCases_a_int32 = int32RandomPInf();
                break;
             case 3:
                subcase = -1;
             case 1:
                testCases_a_int32 = int32NextP2( &sequenceA );
                testCases_done = sequenceA.done;
                break;
            }
            ++subcase;
            break;
#ifdef BITS64
         case testCases_sequence_a_int64:
            switch ( subcase ) {
             case 0:
                testCases_a_int64 = int64RandomP3();
                break;
             case 2:
                testCases_a_int64 = int64RandomPInf();
                break;
             case 3:
                subcase = -1;
             case 1:
                testCases_a_int64 = int64NextP2( &sequenceA );
                testCases_done = sequenceA.done;
                break;
            }
            ++subcase;
            break;
#endif
         case testCases_sequence_a_float32:
            switch ( subcase ) {
             case 0:
                testCases_a_float32 = float32Random();
                break;
             case 1:
                testCases_a_float32 = float32NextQOutP2( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_ab_float32:
            switch ( subcase ) {
             case 0:
                testCases_a_float32 = float32Random();
                testCases_b_float32 = float32Random();
                break;
             case 1:
                if ( sequenceB.done ) {
                    sequenceB.done = FALSE;
                    current_a_float32 = float32NextQInP2( &sequenceA );
                }
                testCases_a_float32 = current_a_float32;
                testCases_b_float32 = float32NextQInP2( &sequenceB );
                testCases_done = sequenceA.done & sequenceB.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_a_float64:
            switch ( subcase ) {
             case 0:
                testCases_a_float64 = float64Random();
                break;
             case 1:
                testCases_a_float64 = float64NextQOutP2( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_ab_float64:
            switch ( subcase ) {
             case 0:
                testCases_a_float64 = float64Random();
                testCases_b_float64 = float64Random();
                break;
             case 1:
                if ( sequenceB.done ) {
                    sequenceB.done = FALSE;
                    current_a_float64 = float64NextQInP2( &sequenceA );
                }
                testCases_a_float64 = current_a_float64;
                testCases_b_float64 = float64NextQInP2( &sequenceB );
                testCases_done = sequenceA.done & sequenceB.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
#ifdef FLOATX80
         case testCases_sequence_a_floatx80:
            switch ( subcase ) {
             case 0:
                testCases_a_floatx80 = floatx80Random();
                break;
             case 1:
                testCases_a_floatx80 = floatx80NextQOutP2( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_ab_floatx80:
            switch ( subcase ) {
             case 0:
                testCases_a_floatx80 = floatx80Random();
                testCases_b_floatx80 = floatx80Random();
                break;
             case 1:
                if ( sequenceB.done ) {
                    sequenceB.done = FALSE;
                    current_a_floatx80 = floatx80NextQInP2( &sequenceA );
                }
                testCases_a_floatx80 = current_a_floatx80;
                testCases_b_floatx80 = floatx80NextQInP2( &sequenceB );
                testCases_done = sequenceA.done & sequenceB.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
#endif
#ifdef FLOAT128
         case testCases_sequence_a_float128:
            switch ( subcase ) {
             case 0:
                testCases_a_float128 = float128Random();
                break;
             case 1:
                testCases_a_float128 = float128NextQOutP2( &sequenceA );
                testCases_done = sequenceA.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
         case testCases_sequence_ab_float128:
            switch ( subcase ) {
             case 0:
                testCases_a_float128 = float128Random();
                testCases_b_float128 = float128Random();
                break;
             case 1:
                if ( sequenceB.done ) {
                    sequenceB.done = FALSE;
                    current_a_float128 = float128NextQInP2( &sequenceA );
                }
                testCases_a_float128 = current_a_float128;
                testCases_b_float128 = float128NextQInP2( &sequenceB );
                testCases_done = sequenceA.done & sequenceB.done;
                subcase = -1;
                break;
            }
            ++subcase;
            break;
#endif
        }
        break;
    }

}