#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ symbol_t ;
struct TYPE_6__ {int buckets; TYPE_3__** table; } ;
typedef  TYPE_2__ hashtable_t ;
struct TYPE_7__ {scalar_t__ data; struct TYPE_7__* next; } ;
typedef  TYPE_3__ hashchain_t ;

/* Variables and functions */
 int abs (int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hashtable_symbol_exists (hashtable_t *H, int hash, char *sym)
{
  hashchain_t *hc;
  symbol_t *s;

  hash = (abs(hash) % H->buckets);
  hc = H->table[hash];
  if (hc == 0)
    {
      /* Empty chain means this symbol has not yet been defined. */
      return 0;
    }
  for (; hc; hc = hc->next)
    {
      s = (symbol_t*)hc->data;
//      if ((hash == s->hash) && (strcmp(sym, s->name) == 0))
/* We _already_ know the hash is the same.  That's why we're probing! */
      if (strcmp(sym, s->name) == 0)
        {
          /* Symbol collisions -- symbol already exists. */
          return 1;
        }
    }
  return 0;  /* Can't find collision. */
}