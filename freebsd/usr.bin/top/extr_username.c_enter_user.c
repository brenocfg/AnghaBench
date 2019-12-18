#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int uid; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ MAXLOGNAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,int) ; 
 TYPE_1__* hash_table ; 
 int hashit (int) ; 
 int /*<<< orphan*/  is_empty_hash (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 

int
enter_user(int uid, char name[], bool wecare)
{
    int hashindex;

#ifdef DEBUG
    fprintf(stderr, "enter_hash(%d, %s, %d)\n", uid, name, wecare);
#endif

    hashindex = hashit(uid);

    if (!is_empty_hash(hashindex))
    {
	if (!wecare)
	    return (0);		/* Don't clobber a slot for trash */
	if (hash_table[hashindex].uid == uid)
	    return(hashindex);	/* Fortuitous find */
    }

    /* empty or wrong slot -- fill it with new value */
    hash_table[hashindex].uid = uid;
    (void) strncpy(hash_table[hashindex].name, name, MAXLOGNAME - 1);
    return(hashindex);
}