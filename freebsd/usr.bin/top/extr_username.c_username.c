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
struct TYPE_2__ {int uid; char* name; } ;

/* Variables and functions */
 int get_user (int) ; 
 TYPE_1__* hash_table ; 
 int hashit (int) ; 
 scalar_t__ is_empty_hash (int) ; 

char *
username(int uid)
{
    int hashindex;

    hashindex = hashit(uid);
    if (is_empty_hash(hashindex) || (hash_table[hashindex].uid != uid))
    {
	/* not here or not right -- get it out of passwd */
	hashindex = get_user(uid);
    }
    return(hash_table[hashindex].name);
}