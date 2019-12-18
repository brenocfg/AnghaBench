#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wordent {int dummy; } ;
struct Hist {unsigned int Hhash; int /*<<< orphan*/  Hlex; } ;

/* Variables and functions */
 int /*<<< orphan*/  createHistHashTable (int) ; 
 struct Hist* deletedHTE ; 
 int /*<<< orphan*/  discardHistHashTable () ; 
 struct Hist* emptyHTE ; 
 unsigned int hash2tableIndex (unsigned int,int) ; 
 scalar_t__ heq (struct wordent*,int /*<<< orphan*/ *) ; 
 struct Hist** histHashTable ; 
 int histHashTableLength ; 

__attribute__((used)) static struct Hist *
findHistHashTable(struct wordent *lp, unsigned hashval)
{
    unsigned deleted = 0;		/* number of deleted entries skipped */
    unsigned hi = hashval;
    struct Hist *hp;
    if (!histHashTable)
	return NULL;
    while ((hi = hash2tableIndex(hi, histHashTableLength)),
           (hp = histHashTable[hi]) != emptyHTE) {
        if (hp == deletedHTE)
	    deleted++;
	else if (hp->Hhash == hashval && heq(lp, &(hp->Hlex)))
            return hp;
	if (deleted > (histHashTableLength>>4)) {
	    /* lots of deletes, so we need a sparser table. */
            discardHistHashTable();
            createHistHashTable(histHashTableLength);
	    return findHistHashTable(lp, hashval);
	}
        hi++;                           /* linear rehash */
    }
    return NULL;
}