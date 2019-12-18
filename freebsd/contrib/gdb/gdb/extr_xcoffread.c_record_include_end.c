#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct coff_symbol {int /*<<< orphan*/  c_value; } ;
struct TYPE_3__ {int /*<<< orphan*/  end; } ;
typedef  TYPE_1__ InclTable ;

/* Variables and functions */
 int /*<<< orphan*/  allocate_include_entry () ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ inclDepth ; 
 size_t inclIndx ; 
 TYPE_1__* inclTable ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static void
record_include_end (struct coff_symbol *cs)
{
  InclTable *pTbl;

  if (inclDepth == 0)
    {
      complaint (&symfile_complaints, "Mismatched C_BINCL/C_EINCL pair");
    }

  allocate_include_entry ();

  pTbl = &inclTable[inclIndx];
  pTbl->end = cs->c_value;

  --inclDepth;
  ++inclIndx;
}