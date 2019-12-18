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
struct TYPE_4__ {char* gen_name; TYPE_3__* type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Symbol ;

/* Variables and functions */
 int FALSE ; 
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
 int TRUE ; 
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
 int /*<<< orphan*/  decode_type (char*,TYPE_3__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ preserve_type (int /*<<< orphan*/ ) ; 

void
generate_type_decode (const Symbol *s)
{
    int preserve = preserve_type(s->name) ? TRUE : FALSE;

    fprintf (codefile, "int ASN1CALL\n"
	     "decode_%s(const unsigned char *p HEIMDAL_UNUSED_ATTRIBUTE,"
	     " size_t len HEIMDAL_UNUSED_ATTRIBUTE, %s *data, size_t *size)\n"
	     "{\n",
	     s->gen_name, s->gen_name);

    switch (s->type->type) {
    case TInteger:
    case TBoolean:
    case TOctetString:
    case TOID:
    case TGeneralizedTime:
    case TGeneralString:
    case TTeletexString:
    case TUTF8String:
    case TPrintableString:
    case TIA5String:
    case TBMPString:
    case TUniversalString:
    case TVisibleString:
    case TUTCTime:
    case TNull:
    case TEnumerated:
    case TBitString:
    case TSequence:
    case TSequenceOf:
    case TSet:
    case TSetOf:
    case TTag:
    case TType:
    case TChoice:
	fprintf (codefile,
		 "size_t ret = 0;\n"
		 "size_t l HEIMDAL_UNUSED_ATTRIBUTE;\n"
		 "int e HEIMDAL_UNUSED_ATTRIBUTE;\n");
	if (preserve)
	    fprintf (codefile, "const unsigned char *begin = p;\n");

	fprintf (codefile, "\n");
	fprintf (codefile, "memset(data, 0, sizeof(*data));\n"); /* hack to avoid `unused variable' */

	decode_type ("data", s->type, 0, "goto fail", "Top", NULL, 1);
	if (preserve)
	    fprintf (codefile,
		     "data->_save.data = calloc(1, ret);\n"
		     "if (data->_save.data == NULL) { \n"
		     "e = ENOMEM; goto fail; \n"
		     "}\n"
		     "data->_save.length = ret;\n"
		     "memcpy(data->_save.data, begin, ret);\n");
	fprintf (codefile,
		 "if(size) *size = ret;\n"
		 "return 0;\n");
	fprintf (codefile,
		 "fail:\n"
		 "free_%s(data);\n"
		 "return e;\n",
		 s->gen_name);
	break;
    default:
	abort ();
    }
    fprintf (codefile, "}\n\n");
}