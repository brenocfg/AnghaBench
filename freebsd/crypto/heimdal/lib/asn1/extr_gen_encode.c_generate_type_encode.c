#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; } ;
struct TYPE_4__ {char* gen_name; TYPE_3__* type; } ;
typedef  TYPE_1__ Symbol ;

/* Variables and functions */
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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  codefile ; 
 int /*<<< orphan*/  encode_type (char*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 

void
generate_type_encode (const Symbol *s)
{
    fprintf (codefile, "int ASN1CALL\n"
	     "encode_%s(unsigned char *p HEIMDAL_UNUSED_ATTRIBUTE, size_t len HEIMDAL_UNUSED_ATTRIBUTE,"
	     " const %s *data, size_t *size)\n"
	     "{\n",
	     s->gen_name, s->gen_name);

    switch (s->type->type) {
    case TInteger:
    case TBoolean:
    case TOctetString:
    case TGeneralizedTime:
    case TGeneralString:
    case TTeletexString:
    case TUTCTime:
    case TUTF8String:
    case TPrintableString:
    case TIA5String:
    case TBMPString:
    case TUniversalString:
    case TVisibleString:
    case TNull:
    case TBitString:
    case TEnumerated:
    case TOID:
    case TSequence:
    case TSequenceOf:
    case TSet:
    case TSetOf:
    case TTag:
    case TType:
    case TChoice:
	fprintf (codefile,
		 "size_t ret HEIMDAL_UNUSED_ATTRIBUTE = 0;\n"
		 "size_t l HEIMDAL_UNUSED_ATTRIBUTE;\n"
		 "int i HEIMDAL_UNUSED_ATTRIBUTE, e HEIMDAL_UNUSED_ATTRIBUTE;\n\n");

	encode_type("data", s->type, "Top");

	fprintf (codefile, "*size = ret;\n"
		 "return 0;\n");
	break;
    default:
	abort ();
    }
    fprintf (codefile, "}\n\n");
}