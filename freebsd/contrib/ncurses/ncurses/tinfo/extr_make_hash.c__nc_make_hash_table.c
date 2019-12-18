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
struct name_table_entry {int nte_link; int /*<<< orphan*/  nte_name; } ;
typedef  int HashValue ;

/* Variables and functions */
 short CAPTABSIZE ; 
 short HASHTABSIZE ; 
 int hash_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,short) ; 

__attribute__((used)) static void
_nc_make_hash_table(struct name_table_entry *table,
		    HashValue * hash_table)
{
    short i;
    int hashvalue;
    int collisions = 0;

    for (i = 0; i < HASHTABSIZE; i++) {
	hash_table[i] = -1;
    }
    for (i = 0; i < CAPTABSIZE; i++) {
	hashvalue = hash_function(table[i].nte_name);

	if (hash_table[hashvalue] >= 0)
	    collisions++;

	if (hash_table[hashvalue] != 0)
	    table[i].nte_link = hash_table[hashvalue];
	hash_table[hashvalue] = i;
    }

    printf("/* %d collisions out of %d entries */\n", collisions, CAPTABSIZE);
}