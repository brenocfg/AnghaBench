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
struct db_table {char* table_name; int table_name_len; } ;
typedef  struct db_table* db_hash_table_p ;

/* Variables and functions */
 int HASH_PRIME ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* zmalloc (int) ; 

struct db_table *get_db_hash (db_hash_table_p db_hash, char *name, int l, int force) {
  int h1 = l, h2 = l, t;
  char *ptr;
  for (ptr = name, t = l; t--; ptr++) {
    if (*ptr >= 'A' && *ptr <= 'Z') {
      *ptr += 32;
    }
    h1 = (h1 * 239 + *ptr) % HASH_PRIME;
    h2 = (h2 * 17 + *ptr) % (HASH_PRIME - 1);
  }
  ++h2;
  while (db_hash[h1].table_name) {
    if (l == db_hash[h1].table_name_len && 
         !memcmp (db_hash[h1].table_name, name, l)) {
      return &db_hash[h1];
    }
    h1 += h2;
    if (h1 >= HASH_PRIME) { 
      h1 -= HASH_PRIME;
    }
  }
  if (force) {
    char *temp = zmalloc (l + 1);
    memcpy (temp, name, l);
    temp[l] = 0;
    db_hash[h1].table_name = temp;
    db_hash[h1].table_name_len = l;
    return &db_hash[h1];
  }
  return 0;
}