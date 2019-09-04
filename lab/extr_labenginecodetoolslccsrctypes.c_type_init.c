#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_25__ ;
typedef  struct TYPE_30__   TYPE_21__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_19__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct TYPE_39__ {int size; int align; int outofline; } ;
struct TYPE_38__ {void* type; } ;
struct TYPE_37__ {TYPE_8__* sym; } ;
struct TYPE_34__ {scalar_t__ p; } ;
struct TYPE_32__ {void* p; } ;
struct TYPE_35__ {TYPE_4__ min; TYPE_2__ max; } ;
struct TYPE_36__ {TYPE_5__ limits; } ;
struct TYPE_33__ {int size; int align; int outofline; } ;
struct TYPE_29__ {int size; int align; int outofline; } ;
struct TYPE_31__ {char unsigned_char; TYPE_3__ ptrmetric; TYPE_9__ longlongmetric; TYPE_9__ intmetric; TYPE_9__ shortmetric; TYPE_9__ longmetric; TYPE_9__ charmetric; TYPE_9__ longdoublemetric; TYPE_9__ floatmetric; TYPE_9__ doublemetric; TYPE_1__ structmetric; } ;
struct TYPE_30__ {int addressed; TYPE_6__ u; } ;
struct TYPE_28__ {scalar_t__ size; scalar_t__ align; } ;
struct TYPE_27__ {scalar_t__ size; scalar_t__ align; TYPE_7__ u; } ;
struct TYPE_26__ {scalar_t__ size; scalar_t__ align; } ;
typedef  TYPE_8__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  FLOAT ; 
 int /*<<< orphan*/  GLOBAL ; 
 int /*<<< orphan*/  INT ; 
 TYPE_25__* IR ; 
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  UNSIGNED ; 
 int /*<<< orphan*/  VOID ; 
 void* charptype ; 
 void* chartype ; 
 void* doubletype ; 
 void* floattype ; 
 void* func (void*,int /*<<< orphan*/ *,int) ; 
 void* funcptype ; 
 void* install (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_19__* inttype ; 
 void* longdouble ; 
 TYPE_19__* longlong ; 
 TYPE_19__* longtype ; 
 scalar_t__ ones (int) ; 
 TYPE_21__* pointersym ; 
 void* ptr (void*) ; 
 TYPE_19__* shorttype ; 
 void* signedchar ; 
 TYPE_19__* signedptr ; 
 int sscanf (char*,char*,int*,int*,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  string (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 void* type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,TYPE_8__*) ; 
 int /*<<< orphan*/  types ; 
 TYPE_10__* unsignedchar ; 
 TYPE_10__* unsignedlong ; 
 TYPE_10__* unsignedlonglong ; 
 TYPE_10__* unsignedptr ; 
 TYPE_10__* unsignedshort ; 
 TYPE_10__* unsignedtype ; 
 TYPE_11__* voidptype ; 
 void* voidtype ; 
 TYPE_10__* widechar ; 
 void* xxinit (int /*<<< orphan*/ ,char*,TYPE_9__) ; 

void type_init(int argc, char *argv[]) {
	static int inited;
	int i;

	if (inited)
		return;
	inited = 1;
	if (!IR)
		return;
	for (i = 1; i < argc; i++) {
		int size, align, outofline;
		if (strncmp(argv[i], "-unsigned_char=", 15) == 0)
			IR->unsigned_char = argv[i][15] - '0';
#define xx(name) \
		else if (sscanf(argv[i], "-" #name "=%d,%d,%d", &size, &align, &outofline) == 3) { \
			IR->name.size = size; IR->name.align = align; \
			IR->name.outofline = outofline; }
	xx(charmetric)
	xx(shortmetric)
	xx(intmetric)
	xx(longmetric)
	xx(longlongmetric)
	xx(floatmetric)
	xx(doublemetric)
	xx(longdoublemetric)
	xx(ptrmetric)
	xx(structmetric)
#undef xx
	}
#define xx(v,name,op,metrics) v=xxinit(op,name,IR->metrics)
	xx(chartype,        "char",              IR->unsigned_char ? UNSIGNED : INT,charmetric);
	xx(doubletype,      "double",            FLOAT,   doublemetric);
	xx(floattype,       "float",             FLOAT,   floatmetric);
	xx(inttype,         "int",               INT,     intmetric);
	xx(longdouble,      "long double",       FLOAT,   longdoublemetric);
	xx(longtype,        "long int",          INT,     longmetric);
	xx(longlong,        "long long int",     INT,     longlongmetric);
	xx(shorttype,       "short",             INT,     shortmetric);
	xx(signedchar,      "signed char",       INT,     charmetric);
	xx(unsignedchar,    "unsigned char",     UNSIGNED,charmetric);
	xx(unsignedlong,    "unsigned long",     UNSIGNED,longmetric);
	xx(unsignedshort,   "unsigned short",    UNSIGNED,shortmetric);
	xx(unsignedtype,    "unsigned int",      UNSIGNED,intmetric);
	xx(unsignedlonglong,"unsigned long long",UNSIGNED,longlongmetric);
#undef xx
	{
		Symbol p;
		p = install(string("void"), &types, GLOBAL, PERM);
		voidtype = type(VOID, NULL, 0, 0, p);
		p->type = voidtype;
	}
	pointersym = install(string("T*"), &types, GLOBAL, PERM);
	pointersym->addressed = IR->ptrmetric.outofline;
	pointersym->u.limits.max.p = (void*)ones(8*IR->ptrmetric.size);
	pointersym->u.limits.min.p = 0;
	voidptype = ptr(voidtype);
	funcptype = ptr(func(voidtype, NULL, 1));
	charptype = ptr(chartype);
#define xx(v,t) if (v==NULL && t->size==voidptype->size && t->align==voidptype->align) v=t
	xx(unsignedptr,unsignedshort);
	xx(unsignedptr,unsignedtype);
	xx(unsignedptr,unsignedlong);
	xx(unsignedptr,unsignedlonglong);
	if (unsignedptr == NULL)
		unsignedptr = type(UNSIGNED, NULL, voidptype->size, voidptype->align, voidptype->u.sym);
	xx(signedptr,shorttype);
	xx(signedptr,inttype);
	xx(signedptr,longtype);
	xx(signedptr,longlong);
	if (signedptr == NULL)
		signedptr = type(INT, NULL, voidptype->size, voidptype->align, voidptype->u.sym);
#undef xx
	widechar = unsignedshort;
	for (i = 0; i < argc; i++) {
#define xx(name,type) \
		if (strcmp(argv[i], "-wchar_t=" #name) == 0) \
			widechar = type;
		xx(unsigned_char,unsignedchar)
		xx(unsigned_int,unsignedtype)
		xx(unsigned_short,unsignedshort)
	}
#undef xx
}