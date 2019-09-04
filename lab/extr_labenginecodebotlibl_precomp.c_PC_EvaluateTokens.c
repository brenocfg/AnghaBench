#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int intvalue; int floatvalue; int parentheses; struct TYPE_12__* next; struct TYPE_12__* prev; } ;
typedef  TYPE_1__ value_t ;
struct TYPE_13__ {int type; int intvalue; int floatvalue; int subtype; int /*<<< orphan*/  string; struct TYPE_13__* next; } ;
typedef  TYPE_2__ token_t ;
struct TYPE_14__ {int /*<<< orphan*/  defines; } ;
typedef  TYPE_3__ source_t ;
struct TYPE_15__ {int operator; scalar_t__ priority; int parentheses; struct TYPE_15__* next; struct TYPE_15__* prev; } ;
typedef  TYPE_4__ operator_t ;

/* Variables and functions */
 int /*<<< orphan*/  AllocOperator (TYPE_4__*) ; 
 int /*<<< orphan*/  AllocValue (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeOperator (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeValue (TYPE_1__*) ; 
 int MAX_OPERATORS ; 
 int MAX_VALUES ; 
 int /*<<< orphan*/  PC_FindDefine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PC_OperatorPriority (int) ; 
#define  P_ADD 154 
#define  P_BIN_AND 153 
#define  P_BIN_NOT 152 
#define  P_BIN_OR 151 
#define  P_BIN_XOR 150 
#define  P_COLON 149 
#define  P_DEC 148 
#define  P_DIV 147 
#define  P_INC 146 
#define  P_LOGIC_AND 145 
#define  P_LOGIC_EQ 144 
#define  P_LOGIC_GEQ 143 
#define  P_LOGIC_GREATER 142 
#define  P_LOGIC_LEQ 141 
#define  P_LOGIC_LESS 140 
#define  P_LOGIC_NOT 139 
#define  P_LOGIC_OR 138 
#define  P_LOGIC_UNEQ 137 
#define  P_LSHIFT 136 
#define  P_MOD 135 
#define  P_MUL 134 
 int P_PARENTHESESCLOSE ; 
 int P_PARENTHESESOPEN ; 
#define  P_QUESTIONMARK 133 
#define  P_RSHIFT 132 
#define  P_SUB 131 
 int /*<<< orphan*/  SourceError (TYPE_3__*,char*,...) ; 
#define  TT_NAME 130 
#define  TT_NUMBER 129 
#define  TT_PUNCTUATION 128 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int PC_EvaluateTokens(source_t *source, token_t *tokens, signed long int *intvalue,
																	float *floatvalue, int integer)
{
	operator_t *o, *firstoperator, *lastoperator;
	value_t *v, *firstvalue, *lastvalue, *v1, *v2;
	token_t *t;
	int brace = 0;
	int parentheses = 0;
	int error = 0;
	int lastwasvalue = 0;
	int negativevalue = 0;
	int questmarkintvalue = 0;
	float questmarkfloatvalue = 0;
	int gotquestmarkvalue = qfalse;
	//
	operator_t operator_heap[MAX_OPERATORS];
	int numoperators = 0;
	value_t value_heap[MAX_VALUES];
	int numvalues = 0;

	firstoperator = lastoperator = NULL;
	firstvalue = lastvalue = NULL;
	if (intvalue) *intvalue = 0;
	if (floatvalue) *floatvalue = 0;
	for (t = tokens; t; t = t->next)
	{
		switch(t->type)
		{
			case TT_NAME:
			{
				if (lastwasvalue || negativevalue)
				{
					SourceError(source, "syntax error in #if/#elif");
					error = 1;
					break;
				} //end if
				if (strcmp(t->string, "defined"))
				{
					SourceError(source, "undefined name %s in #if/#elif", t->string);
					error = 1;
					break;
				} //end if
				t = t->next;
				if (!strcmp(t->string, "("))
				{
					brace = qtrue;
					t = t->next;
				} //end if
				if (!t || t->type != TT_NAME)
				{
					SourceError(source, "defined without name in #if/#elif");
					error = 1;
					break;
				} //end if
				//v = (value_t *) GetClearedMemory(sizeof(value_t));
				AllocValue(v);
#if DEFINEHASHING
				if (PC_FindHashedDefine(source->definehash, t->string))
#else			
				if (PC_FindDefine(source->defines, t->string))
#endif //DEFINEHASHING
				{
					v->intvalue = 1;
					v->floatvalue = 1;
				} //end if
				else
				{
					v->intvalue = 0;
					v->floatvalue = 0;
				} //end else
				v->parentheses = parentheses;
				v->next = NULL;
				v->prev = lastvalue;
				if (lastvalue) lastvalue->next = v;
				else firstvalue = v;
				lastvalue = v;
				if (brace)
				{
					t = t->next;
					if (!t || strcmp(t->string, ")"))
					{
						SourceError(source, "defined without ) in #if/#elif");
						error = 1;
						break;
					} //end if
				} //end if
				brace = qfalse;
				// defined() creates a value
				lastwasvalue = 1;
				break;
			} //end case
			case TT_NUMBER:
			{
				if (lastwasvalue)
				{
					SourceError(source, "syntax error in #if/#elif");
					error = 1;
					break;
				} //end if
				//v = (value_t *) GetClearedMemory(sizeof(value_t));
				AllocValue(v);
				if (negativevalue)
				{
					v->intvalue = - (signed int) t->intvalue;
					v->floatvalue = - t->floatvalue;
				} //end if
				else
				{
					v->intvalue = t->intvalue;
					v->floatvalue = t->floatvalue;
				} //end else
				v->parentheses = parentheses;
				v->next = NULL;
				v->prev = lastvalue;
				if (lastvalue) lastvalue->next = v;
				else firstvalue = v;
				lastvalue = v;
				//last token was a value
				lastwasvalue = 1;
				//
				negativevalue = 0;
				break;
			} //end case
			case TT_PUNCTUATION:
			{
				if (negativevalue)
				{
					SourceError(source, "misplaced minus sign in #if/#elif");
					error = 1;
					break;
				} //end if
				if (t->subtype == P_PARENTHESESOPEN)
				{
					parentheses++;
					break;
				} //end if
				else if (t->subtype == P_PARENTHESESCLOSE)
				{
					parentheses--;
					if (parentheses < 0)
					{
						SourceError(source, "too many ) in #if/#elsif");
						error = 1;
					} //end if
					break;
				} //end else if
				//check for invalid operators on floating point values
				if (!integer)
				{
					if (t->subtype == P_BIN_NOT || t->subtype == P_MOD ||
						t->subtype == P_RSHIFT || t->subtype == P_LSHIFT ||
						t->subtype == P_BIN_AND || t->subtype == P_BIN_OR ||
						t->subtype == P_BIN_XOR)
					{
						SourceError(source, "illigal operator %s on floating point operands", t->string);
						error = 1;
						break;
					} //end if
				} //end if
				switch(t->subtype)
				{
					case P_LOGIC_NOT:
					case P_BIN_NOT:
					{
						if (lastwasvalue)
						{
							SourceError(source, "! or ~ after value in #if/#elif");
							error = 1;
							break;
						} //end if
						break;
					} //end case
					case P_INC:
					case P_DEC:
					{
						SourceError(source, "++ or -- used in #if/#elif");
						break;
					} //end case
					case P_SUB:
					{
						if (!lastwasvalue)
						{
							negativevalue = 1;
							break;
						} //end if
					} //end case
					
					case P_MUL:
					case P_DIV:
					case P_MOD:
					case P_ADD:

					case P_LOGIC_AND:
					case P_LOGIC_OR:
					case P_LOGIC_GEQ:
					case P_LOGIC_LEQ:
					case P_LOGIC_EQ:
					case P_LOGIC_UNEQ:

					case P_LOGIC_GREATER:
					case P_LOGIC_LESS:

					case P_RSHIFT:
					case P_LSHIFT:

					case P_BIN_AND:
					case P_BIN_OR:
					case P_BIN_XOR:

					case P_COLON:
					case P_QUESTIONMARK:
					{
						if (!lastwasvalue)
						{
							SourceError(source, "operator %s after operator in #if/#elif", t->string);
							error = 1;
							break;
						} //end if
						break;
					} //end case
					default:
					{
						SourceError(source, "invalid operator %s in #if/#elif", t->string);
						error = 1;
						break;
					} //end default
				} //end switch
				if (!error && !negativevalue)
				{
					//o = (operator_t *) GetClearedMemory(sizeof(operator_t));
					AllocOperator(o);
					o->operator = t->subtype;
					o->priority = PC_OperatorPriority(t->subtype);
					o->parentheses = parentheses;
					o->next = NULL;
					o->prev = lastoperator;
					if (lastoperator) lastoperator->next = o;
					else firstoperator = o;
					lastoperator = o;
					lastwasvalue = 0;
				} //end if
				break;
			} //end case
			default:
			{
				SourceError(source, "unknown %s in #if/#elif", t->string);
				error = 1;
				break;
			} //end default
		} //end switch
		if (error) break;
	} //end for
	if (!error)
	{
		if (!lastwasvalue)
		{
			SourceError(source, "trailing operator in #if/#elif");
			error = 1;
		} //end if
		else if (parentheses)
		{
			SourceError(source, "too many ( in #if/#elif");
			error = 1;
		} //end else if
	} //end if
	//
	gotquestmarkvalue = qfalse;
	questmarkintvalue = 0;
	questmarkfloatvalue = 0;
	//while there are operators
	while(!error && firstoperator)
	{
		v = firstvalue;
		for (o = firstoperator; o->next; o = o->next)
		{
			//if the current operator is nested deeper in parentheses
			//than the next operator
			if (o->parentheses > o->next->parentheses) break;
			//if the current and next operator are nested equally deep in parentheses
			if (o->parentheses == o->next->parentheses)
			{
				//if the priority of the current operator is equal or higher
				//than the priority of the next operator
				if (o->priority >= o->next->priority) break;
			} //end if
			//if the arity of the operator isn't equal to 1
			if (o->operator != P_LOGIC_NOT
					&& o->operator != P_BIN_NOT) v = v->next;
			//if there's no value or no next value
			if (!v)
			{
				SourceError(source, "mising values in #if/#elif");
				error = 1;
				break;
			} //end if
		} //end for
		if (error) break;
		v1 = v;
		v2 = v->next;
#ifdef DEBUG_EVAL
		if (integer)
		{
			Log_Write("operator %s, value1 = %d", PunctuationFromNum(source->scriptstack, o->operator), v1->intvalue);
			if (v2) Log_Write("value2 = %d", v2->intvalue);
		} //end if
		else
		{
			Log_Write("operator %s, value1 = %f", PunctuationFromNum(source->scriptstack, o->operator), v1->floatvalue);
			if (v2) Log_Write("value2 = %f", v2->floatvalue);
		} //end else
#endif //DEBUG_EVAL
		switch(o->operator)
		{
			case P_LOGIC_NOT:		v1->intvalue = !v1->intvalue;
									v1->floatvalue = !v1->floatvalue; break;
			case P_BIN_NOT:			v1->intvalue = ~v1->intvalue;
									break;
			case P_MUL:				v1->intvalue *= v2->intvalue;
									v1->floatvalue *= v2->floatvalue; break;
			case P_DIV:				if (!v2->intvalue || !v2->floatvalue)
									{
										SourceError(source, "divide by zero in #if/#elif");
										error = 1;
										break;
									}
									v1->intvalue /= v2->intvalue;
									v1->floatvalue /= v2->floatvalue; break;
			case P_MOD:				if (!v2->intvalue)
									{
										SourceError(source, "divide by zero in #if/#elif");
										error = 1;
										break;
									}
									v1->intvalue %= v2->intvalue; break;
			case P_ADD:				v1->intvalue += v2->intvalue;
									v1->floatvalue += v2->floatvalue; break;
			case P_SUB:				v1->intvalue -= v2->intvalue;
									v1->floatvalue -= v2->floatvalue; break;
			case P_LOGIC_AND:		v1->intvalue = v1->intvalue && v2->intvalue;
									v1->floatvalue = v1->floatvalue && v2->floatvalue; break;
			case P_LOGIC_OR:		v1->intvalue = v1->intvalue || v2->intvalue;
									v1->floatvalue = v1->floatvalue || v2->floatvalue; break;
			case P_LOGIC_GEQ:		v1->intvalue = v1->intvalue >= v2->intvalue;
									v1->floatvalue = v1->floatvalue >= v2->floatvalue; break;
			case P_LOGIC_LEQ:		v1->intvalue = v1->intvalue <= v2->intvalue;
									v1->floatvalue = v1->floatvalue <= v2->floatvalue; break;
			case P_LOGIC_EQ:		v1->intvalue = v1->intvalue == v2->intvalue;
									v1->floatvalue = v1->floatvalue == v2->floatvalue; break;
			case P_LOGIC_UNEQ:		v1->intvalue = v1->intvalue != v2->intvalue;
									v1->floatvalue = v1->floatvalue != v2->floatvalue; break;
			case P_LOGIC_GREATER:	v1->intvalue = v1->intvalue > v2->intvalue;
									v1->floatvalue = v1->floatvalue > v2->floatvalue; break;
			case P_LOGIC_LESS:		v1->intvalue = v1->intvalue < v2->intvalue;
									v1->floatvalue = v1->floatvalue < v2->floatvalue; break;
			case P_RSHIFT:			v1->intvalue >>= v2->intvalue;
									break;
			case P_LSHIFT:			v1->intvalue <<= v2->intvalue;
									break;
			case P_BIN_AND:			v1->intvalue &= v2->intvalue;
									break;
			case P_BIN_OR:			v1->intvalue |= v2->intvalue;
									break;
			case P_BIN_XOR:			v1->intvalue ^= v2->intvalue;
									break;
			case P_COLON:
			{
				if (!gotquestmarkvalue)
				{
					SourceError(source, ": without ? in #if/#elif");
					error = 1;
					break;
				} //end if
				if (integer)
				{
					if (!questmarkintvalue) v1->intvalue = v2->intvalue;
				} //end if
				else
				{
					if (!questmarkfloatvalue) v1->floatvalue = v2->floatvalue;
				} //end else
				gotquestmarkvalue = qfalse;
				break;
			} //end case
			case P_QUESTIONMARK:
			{
				if (gotquestmarkvalue)
				{
					SourceError(source, "? after ? in #if/#elif");
					error = 1;
					break;
				} //end if
				questmarkintvalue = v1->intvalue;
				questmarkfloatvalue = v1->floatvalue;
				gotquestmarkvalue = qtrue;
				break;
			} //end if
		} //end switch
#ifdef DEBUG_EVAL
		if (integer) Log_Write("result value = %d", v1->intvalue);
		else Log_Write("result value = %f", v1->floatvalue);
#endif //DEBUG_EVAL
		if (error) break;
		//if not an operator with arity 1
		if (o->operator != P_LOGIC_NOT
				&& o->operator != P_BIN_NOT)
		{
			//remove the second value if not question mark operator
			if (o->operator != P_QUESTIONMARK) v = v->next;
			//
			if (v)
			{
				if (v->prev) v->prev->next = v->next;
				else firstvalue = v->next;
				if (v->next) v->next->prev = v->prev;
			}
			//FreeMemory(v);
			FreeValue(v);
		} //end if
		//remove the operator
		if (o->prev) o->prev->next = o->next;
		else firstoperator = o->next;
		if (o->next) o->next->prev = o->prev;
		//FreeMemory(o);
		FreeOperator(o);
	} //end while
	if (firstvalue)
	{
		if (intvalue) *intvalue = firstvalue->intvalue;
		if (floatvalue) *floatvalue = firstvalue->floatvalue;
	} //end if
	for (o = firstoperator; o; o = lastoperator)
	{
		lastoperator = o->next;
		//FreeMemory(o);
		FreeOperator(o);
	} //end for
	for (v = firstvalue; v; v = lastvalue)
	{
		lastvalue = v->next;
		//FreeMemory(v);
		FreeValue(v);
	} //end for
	if (!error) return qtrue;
	if (intvalue) *intvalue = 0;
	if (floatvalue) *floatvalue = 0;
	return qfalse;
}