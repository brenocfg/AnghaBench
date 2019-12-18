#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int buckets; TYPE_2__** table; } ;
typedef  TYPE_1__ hashtable_t ;
struct TYPE_5__ {struct TYPE_5__* next; void* data; } ;
typedef  TYPE_2__ hashchain_t ;

/* Variables and functions */
 int abs (int) ; 
 void* calloc (int,int) ; 

__attribute__((used)) static void hashtable_add (hashtable_t *H, int hashvalue, void *datum)
{
  hashchain_t *hc, **hb;

  hashvalue = (abs(hashvalue) % H->buckets);
  hb = &(H->table[hashvalue]);
  if (*hb == 0)
    {
      /* Empty bucket.  Create new one. */
      *hb = calloc(1, sizeof(**hb));
      hc = *hb;
    }
  else
    {
      /* Get hc to point to last node in chain. */
      for (hc = *hb; hc && hc->next; hc = hc->next);
      hc->next = calloc(1, sizeof(*hc));
      hc = hc->next;
    }
  hc->data = datum;
  hc->next = 0;
}