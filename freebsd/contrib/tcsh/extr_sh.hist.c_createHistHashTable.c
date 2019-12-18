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
struct Hist {unsigned int Hhash; int /*<<< orphan*/  Hlex; struct Hist* Hnext; } ;

/* Variables and functions */
 struct Hist Histlist ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  discardHistHashTable () ; 
 scalar_t__ emptyHTE ; 
 int getHashTableSize (int) ; 
 unsigned int hashhist (int /*<<< orphan*/ *) ; 
 int histCount ; 
 scalar_t__* histHashTable ; 
 int histHashTableLength ; 
 int histlen ; 
 int /*<<< orphan*/  insertHistHashTable (struct Hist*,unsigned int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* xmalloc (int) ; 

__attribute__((used)) static void
createHistHashTable(int hlen)
{
    if (hlen == 0) {
	discardHistHashTable();
        return;
    }
    if (hlen < 0) {
	if (histlen <= 0)
	    return;			/* no need for hash table */
	hlen = histlen;
    }
    if (histHashTable != NULL) {
	if (histCount < histHashTableLength * 3 / 4)
	    return;			/* good enough for now */
	discardHistHashTable();		/* too small */
    }
    histHashTableLength = getHashTableSize(
	hlen > (int)histCount ? hlen : (int)histCount);
    histHashTable = xmalloc(histHashTableLength * sizeof(struct Hist *));
    memset(histHashTable, 0, histHashTableLength * sizeof(struct Hist *));
    assert(histHashTable[0] == emptyHTE);

    /* Now insert all the entries on the history list into the hash table. */
    {
        struct Hist *hp;
        for (hp = &Histlist; (hp = hp->Hnext) != NULL;) {
            unsigned lpHash = hashhist(&hp->Hlex);
            assert(!hp->Hhash || hp->Hhash == lpHash);
            hp->Hhash = 0;              /* force insert to new hash table */
            insertHistHashTable(hp, lpHash);
        }
    }
}