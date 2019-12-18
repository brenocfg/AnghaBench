#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int tagvalue; int /*<<< orphan*/  tagclass; } ;
struct TYPE_9__ {int type; TYPE_3__* symbol; TYPE_2__ tag; TYPE_1__* subtype; } ;
typedef  TYPE_4__ Type ;
struct TYPE_8__ {TYPE_4__* type; int /*<<< orphan*/  name; int /*<<< orphan*/  stype; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  Der_type ;
typedef  int /*<<< orphan*/  Der_class ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_C_UNIV ; 
 int /*<<< orphan*/  CONS ; 
 int /*<<< orphan*/  PRIM ; 
 int /*<<< orphan*/  SUndefined ; 
 int /*<<< orphan*/  Stype ; 
#define  TBMPString 151 
#define  TBitString 150 
#define  TBoolean 149 
#define  TChoice 148 
#define  TEnumerated 147 
#define  TGeneralString 146 
#define  TGeneralizedTime 145 
#define  TIA5String 144 
#define  TInteger 143 
#define  TNull 142 
#define  TOID 141 
#define  TOctetString 140 
#define  TPrintableString 139 
#define  TSequence 138 
#define  TSequenceOf 137 
#define  TSet 136 
#define  TSetOf 135 
#define  TTag 134 
#define  TTeletexString 133 
#define  TType 132 
#define  TUTCTime 131 
#define  TUTF8String 130 
#define  TUniversalString 129 
#define  TVisibleString 128 
 unsigned int UT_BMPString ; 
 unsigned int UT_BitString ; 
 unsigned int UT_Boolean ; 
 unsigned int UT_Enumerated ; 
 unsigned int UT_GeneralString ; 
 unsigned int UT_GeneralizedTime ; 
 unsigned int UT_IA5String ; 
 unsigned int UT_Integer ; 
 unsigned int UT_Null ; 
 unsigned int UT_OID ; 
 unsigned int UT_OctetString ; 
 unsigned int UT_PrintableString ; 
 unsigned int UT_Sequence ; 
 unsigned int UT_Set ; 
 unsigned int UT_TeletexString ; 
 unsigned int UT_UTCTime ; 
 unsigned int UT_UTF8String ; 
 unsigned int UT_UniversalString ; 
 unsigned int UT_VisibleString ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  is_primitive_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lex_error_message (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_tag (const Type *t,
	  Der_class *cl, Der_type *ty, unsigned *tag)
{
    switch (t->type) {
    case TBitString:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_BitString;
	break;
    case TBoolean:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_Boolean;
	break;
    case TChoice:
	errx(1, "Cannot have recursive CHOICE");
    case TEnumerated:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_Enumerated;
	break;
    case TGeneralString:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_GeneralString;
	break;
    case TTeletexString:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_TeletexString;
	break;
    case TGeneralizedTime:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_GeneralizedTime;
	break;
    case TIA5String:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_IA5String;
	break;
    case TInteger:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_Integer;
	break;
    case TNull:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_Null;
	break;
    case TOID:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_OID;
	break;
    case TOctetString:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_OctetString;
	break;
    case TPrintableString:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_PrintableString;
	break;
    case TSequence:
    case TSequenceOf:
	*cl  = ASN1_C_UNIV;
	*ty  = CONS;
	*tag = UT_Sequence;
	break;
    case TSet:
    case TSetOf:
	*cl  = ASN1_C_UNIV;
	*ty  = CONS;
	*tag = UT_Set;
	break;
    case TTag:
	*cl  = t->tag.tagclass;
	*ty  = is_primitive_type(t->subtype->type) ? PRIM : CONS;
	*tag = t->tag.tagvalue;
	break;
    case TType:
	if ((t->symbol->stype == Stype && t->symbol->type == NULL)
	    || t->symbol->stype == SUndefined) {
	    lex_error_message("%s is imported or still undefined, "
			      " can't generate tag checking data in CHOICE "
			      "without this information",
			      t->symbol->name);
	    exit(1);
	}
	find_tag(t->symbol->type, cl, ty, tag);
	return;
    case TUTCTime:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_UTCTime;
	break;
    case TUTF8String:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_UTF8String;
	break;
    case TBMPString:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_BMPString;
	break;
    case TUniversalString:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_UniversalString;
	break;
    case TVisibleString:
	*cl  = ASN1_C_UNIV;
	*ty  = PRIM;
	*tag = UT_VisibleString;
	break;
    default:
	abort();
    }
}