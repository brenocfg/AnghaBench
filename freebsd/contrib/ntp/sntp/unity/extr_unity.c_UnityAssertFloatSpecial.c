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
typedef  int _U_SINT ;
typedef  float _UF ;
typedef  int /*<<< orphan*/  UNITY_LINE_TYPE ;
typedef  int UNITY_FLOAT_TRAIT_T ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_FAIL_AND_BAIL ; 
#define  UNITY_FLOAT_IS_DET 135 
#define  UNITY_FLOAT_IS_INF 134 
#define  UNITY_FLOAT_IS_NAN 133 
#define  UNITY_FLOAT_IS_NEG_INF 132 
#define  UNITY_FLOAT_IS_NOT_DET 131 
#define  UNITY_FLOAT_IS_NOT_INF 130 
#define  UNITY_FLOAT_IS_NOT_NAN 129 
#define  UNITY_FLOAT_IS_NOT_NEG_INF 128 
 int /*<<< orphan*/  UNITY_SKIP_EXECUTION ; 
 int /*<<< orphan*/  UnityAddMsgIfSpecified (char const*) ; 
 int /*<<< orphan*/  UnityPrint (char const*) ; 
 int /*<<< orphan*/  UnityPrintFloat (float const) ; 
 char const* UnityStrDet ; 
 char const* UnityStrExpected ; 
 char const* UnityStrInf ; 
 char const* UnityStrNaN ; 
 char const* UnityStrNegInf ; 
 char const* UnityStrNot ; 
 char const* UnityStrWas ; 
 int /*<<< orphan*/  UnityTestResultsFailBegin (int /*<<< orphan*/  const) ; 
 float f_zero ; 

void UnityAssertFloatSpecial(const _UF actual,
                             const char* msg,
                             const UNITY_LINE_TYPE lineNumber,
                             const UNITY_FLOAT_TRAIT_T style)
{
    const char* trait_names[] = { UnityStrInf, UnityStrNegInf, UnityStrNaN, UnityStrDet };
    _U_SINT should_be_trait   = ((_U_SINT)style & 1);
    _U_SINT is_trait          = !should_be_trait;
    _U_SINT trait_index       = style >> 1;

    UNITY_SKIP_EXECUTION;

    switch(style)
    {
        //To determine Inf / Neg Inf, we compare to an Inf / Neg Inf value we create on the fly
        //We are using a variable to hold the zero value because some compilers complain about dividing by zero otherwise
        case UNITY_FLOAT_IS_INF:
        case UNITY_FLOAT_IS_NOT_INF:
            is_trait = ((1.0f / f_zero) == actual) ? 1 : 0;
            break;
        case UNITY_FLOAT_IS_NEG_INF:
        case UNITY_FLOAT_IS_NOT_NEG_INF:
            is_trait = ((-1.0f / f_zero) == actual) ? 1 : 0;
            break;

        //NaN is the only floating point value that does NOT equal itself. Therefore if Actual == Actual, then it is NOT NaN.
        case UNITY_FLOAT_IS_NAN:
        case UNITY_FLOAT_IS_NOT_NAN:
            is_trait = (actual == actual) ? 0 : 1;
            break;

        //A determinate number is non infinite and not NaN. (therefore the opposite of the two above)
        case UNITY_FLOAT_IS_DET:
        case UNITY_FLOAT_IS_NOT_DET:
            if ( (actual != actual) || ((1.0f / f_zero) == actual) || ((-1.0f / f_zero) == actual) )
                is_trait = 0;
            else
                is_trait = 1;
            break;
	default:
	    ;
    }

    if (is_trait != should_be_trait)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrExpected);
        if (!should_be_trait)
            UnityPrint(UnityStrNot);
        UnityPrint(trait_names[trait_index]);
        UnityPrint(UnityStrWas);
#ifdef UNITY_FLOAT_VERBOSE
        UnityPrintFloat(actual);
#else
        if (should_be_trait)
            UnityPrint(UnityStrNot);
        UnityPrint(trait_names[trait_index]);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
}