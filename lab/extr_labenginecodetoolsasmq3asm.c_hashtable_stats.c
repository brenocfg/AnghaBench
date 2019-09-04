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
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_2__ hashchain_t ;

/* Variables and functions */
 int /*<<< orphan*/  report (char*,...) ; 

__attribute__((used)) static void hashtable_stats (hashtable_t *H)
{
  int len, empties, longest, nodes;
  int i;
  float meanlen;
  hashchain_t *hc;

  report("Stats for hashtable %08X", H);
  empties = 0;
  longest = 0;
  nodes = 0;
  for (i = 0; i < H->buckets; i++)
    {
      if (H->table[i] == 0)
        { empties++; continue; }
      for (hc = H->table[i], len = 0; hc; hc = hc->next, len++);
      if (len > longest) { longest = len; }
      nodes += len;
    }
  meanlen = (float)(nodes) / (H->buckets - empties);
#if 0
/* Long stats display */
  report(" Total buckets: %d\n", H->buckets);
  report(" Total stored nodes: %d\n", nodes);
  report(" Longest chain: %d\n", longest);
  report(" Empty chains: %d\n", empties);
  report(" Mean non-empty chain length: %f\n", meanlen);
#else //0
/* Short stats display */
  report(", %d buckets, %d nodes", H->buckets, nodes);
  report("\n");
  report(" Longest chain: %d, empty chains: %d, mean non-empty: %f", longest, empties, meanlen);
#endif //0
  report("\n");
}