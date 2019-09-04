#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_1__ symbol_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__* lastSymbol ; 
 TYPE_1__** malloc (int) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* symbols ; 
 int /*<<< orphan*/  symlist_cmp ; 

__attribute__((used)) static void sort_symbols ()
{
  int i, elems;
  symbol_t *s;
  symbol_t **symlist;

  if(!symbols)
  	return;

//crumb("sort_symbols: Constructing symlist array\n");
  for (elems = 0, s = symbols; s; s = s->next, elems++) /* nop */ ;

  symlist = malloc(elems * sizeof(symbol_t*));
  for (i = 0, s = symbols; s; s = s->next, i++)
    {
      symlist[i] = s;
    }
//crumbf("sort_symbols: Quick-sorting %d symbols\n", elems);
  qsort(symlist, elems, sizeof(symbol_t*), symlist_cmp);
//crumbf("sort_symbols: Reconstructing symbols list\n");
  s = symbols = symlist[0];
  for (i = 1; i < elems; i++)
    {
      s->next = symlist[i];
      s = s->next;
    }
  lastSymbol = s;
  s->next = 0;
//crumbf("sort_symbols: verifying..."); fflush(stdout);
  for (i = 0, s = symbols; s; s = s->next, i++) /*nop*/ ;
//crumbf(" %d elements\n", i);
  free(symlist);  /* d'oh.  no gc. */
}