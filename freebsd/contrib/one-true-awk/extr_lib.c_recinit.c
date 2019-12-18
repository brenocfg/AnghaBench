#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* sval; int /*<<< orphan*/  nval; } ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 TYPE_1__ dollar0 ; 
 char* fields ; 
 TYPE_1__** fldtab ; 
 int /*<<< orphan*/  makefields (int,int) ; 
 scalar_t__ malloc (int) ; 
 int nfields ; 
 char* record ; 
 int /*<<< orphan*/  tostring (char*) ; 

void recinit(unsigned int n)
{
	if ( (record = (char *) malloc(n)) == NULL
	  || (fields = (char *) malloc(n+1)) == NULL
	  || (fldtab = (Cell **) malloc((nfields+2) * sizeof(Cell *))) == NULL
	  || (fldtab[0] = (Cell *) malloc(sizeof(Cell))) == NULL )
		FATAL("out of space for $0 and fields");
	*record = '\0';
	*fldtab[0] = dollar0;
	fldtab[0]->sval = record;
	fldtab[0]->nval = tostring("0");
	makefields(1, nfields);
}