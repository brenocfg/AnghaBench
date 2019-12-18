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
struct TYPE_2__ {int* Booleans; int* Numbers; int /*<<< orphan*/ * Strings; } ;
typedef  int PredType ;
typedef  size_t PredIdx ;

/* Variables and functions */
 int ABSENT_NUMERIC ; 
 int /*<<< orphan*/  ABSENT_STRING ; 
#define  BOOLEAN 130 
 int FAIL ; 
 int FALSE ; 
#define  NUMBER 129 
#define  STRING 128 
 scalar_t__ TRUE ; 
 TYPE_1__* cur_type ; 

__attribute__((used)) static int
dump_predicate(PredType type, PredIdx idx)
/* predicate function to use for ordinary decompilation */
{
    switch (type) {
    case BOOLEAN:
	return (cur_type->Booleans[idx] == FALSE)
	    ? FAIL : cur_type->Booleans[idx];

    case NUMBER:
	return (cur_type->Numbers[idx] == ABSENT_NUMERIC)
	    ? FAIL : cur_type->Numbers[idx];

    case STRING:
	return (cur_type->Strings[idx] != ABSENT_STRING)
	    ? (int) TRUE : FAIL;
    }

    return (FALSE);		/* pacify compiler */
}