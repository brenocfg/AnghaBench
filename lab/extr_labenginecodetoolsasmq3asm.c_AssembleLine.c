#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int opcode; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ sourceOps_t ;
struct TYPE_6__ {scalar_t__ data; struct TYPE_6__* next; } ;
typedef  TYPE_2__ hashchain_t ;

/* Variables and functions */
 size_t CODESEG ; 
 int /*<<< orphan*/  CodeError (char*,char*) ; 
 int /*<<< orphan*/  EmitByte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EmitInt (int /*<<< orphan*/ *,int) ; 
 int HashString (char*) ; 
 int OP_BLOCK_COPY ; 
 int OP_CVFI ; 
 int OP_CVIF ; 
 int OP_IGNORE ; 
 int OP_SEX16 ; 
 int OP_SEX8 ; 
 int OP_UNDEF ; 
 int /*<<< orphan*/  Parse () ; 
 int ParseExpression () ; 
 scalar_t__ TryAssembleADDRESS () ; 
 scalar_t__ TryAssembleADDRF () ; 
 scalar_t__ TryAssembleADDRL () ; 
 scalar_t__ TryAssembleALIGN () ; 
 scalar_t__ TryAssembleARG () ; 
 scalar_t__ TryAssembleBSS () ; 
 scalar_t__ TryAssembleBYTE () ; 
 scalar_t__ TryAssembleCALL () ; 
 scalar_t__ TryAssembleCODE () ; 
 scalar_t__ TryAssembleDATA () ; 
 scalar_t__ TryAssembleENDPROC () ; 
 scalar_t__ TryAssembleEQU () ; 
 scalar_t__ TryAssembleEXPORT () ; 
 scalar_t__ TryAssembleFILE () ; 
 scalar_t__ TryAssembleIMPORT () ; 
 scalar_t__ TryAssembleLABEL () ; 
 scalar_t__ TryAssembleLINE () ; 
 scalar_t__ TryAssembleLIT () ; 
 scalar_t__ TryAssemblePOP () ; 
 scalar_t__ TryAssemblePROC () ; 
 scalar_t__ TryAssembleRET () ; 
 scalar_t__ TryAssembleSKIP () ; 
 TYPE_2__* hashtable_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  instructionCount ; 
 int* opcodesHash ; 
 int /*<<< orphan*/  optable ; 
 int /*<<< orphan*/ * segment ; 
 TYPE_1__* sourceOps ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 char* token ; 

__attribute__((used)) static void AssembleLine( void ) {
	hashchain_t *hc;
	sourceOps_t *op;
	int		i;
	int		hash;

	Parse();
	if ( !token[0] ) {
		return;
	}

	hash = HashString( token );

/*
  Opcode search using hash table.
  Since the opcodes stays mostly fixed, this may benefit even more from a tree.
  Always with the tree :)
 -PH
*/
	for (hc = hashtable_get(optable, hash); hc; hc = hc->next) {
		op = (sourceOps_t*)(hc->data);
		i = op - sourceOps;
		if ((hash == opcodesHash[i]) && (!strcmp(token, op->name))) {
			int		opcode;
			int		expression;

			if ( op->opcode == OP_UNDEF ) {
				CodeError( "Undefined opcode: %s\n", token );
			}
			if ( op->opcode == OP_IGNORE ) {
				return;		// we ignore most conversions
			}

			// sign extensions need to check next parm
			opcode = op->opcode;
			if ( opcode == OP_SEX8 ) {
				Parse();
				if ( token[0] == '1' ) {
					opcode = OP_SEX8;
				} else if ( token[0] == '2' ) {
					opcode = OP_SEX16;
				} else {
					CodeError( "Bad sign extension: %s\n", token );
					return;
				}
			}

			// check for expression
			Parse();
			if ( token[0] && op->opcode != OP_CVIF
					&& op->opcode != OP_CVFI ) {
				expression = ParseExpression();

				// code like this can generate non-dword block copies:
				// auto char buf[2] = " ";
				// we are just going to round up.  This might conceivably
				// be incorrect if other initialized chars follow.
				if ( opcode == OP_BLOCK_COPY ) {
					expression = ( expression + 3 ) & ~3;
				}

				EmitByte( &segment[CODESEG], opcode );
				EmitInt( &segment[CODESEG], expression );
			} else {
				EmitByte( &segment[CODESEG], opcode );
			}

			instructionCount++;
			return;
		}
	}

/* This falls through if an assembly opcode is not found.  -PH */

/* The following should be sorted in sequence of statistical frequency, most frequent first.  -PH */
/*
Empirical frequency statistics from FI 2001.01.23:
 109892	STAT ADDRL
  72188	STAT BYTE
  51150	STAT LINE
  50906	STAT ARG
  43704	STAT IMPORT
  34902	STAT LABEL
  32066	STAT ADDRF
  23704	STAT CALL
   7720	STAT POP
   7256	STAT RET
   5198	STAT ALIGN
   3292	STAT EXPORT
   2878	STAT PROC
   2878	STAT ENDPROC
   2812	STAT ADDRESS
    738	STAT SKIP
    374	STAT EQU
    280	STAT CODE
    176	STAT LIT
    102	STAT FILE
    100	STAT BSS
     68	STAT DATA

 -PH
*/

#undef ASM
#define ASM(O) if (TryAssemble##O ()) return;

	ASM(ADDRL)
	ASM(BYTE)
	ASM(LINE)
	ASM(ARG)
	ASM(IMPORT)
	ASM(LABEL)
	ASM(ADDRF)
	ASM(CALL)
	ASM(POP)
	ASM(RET)
	ASM(ALIGN)
	ASM(EXPORT)
	ASM(PROC)
	ASM(ENDPROC)
	ASM(ADDRESS)
	ASM(SKIP)
	ASM(EQU)
	ASM(CODE)
	ASM(LIT)
	ASM(FILE)
	ASM(BSS)
	ASM(DATA)

	CodeError( "Unknown token: %s\n", token );
}