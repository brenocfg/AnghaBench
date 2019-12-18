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
struct TYPE_4__ {TYPE_2__* fsap_data; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ svn_fs_id_t ;
struct TYPE_5__ {char* node_id; char* copy_id; char* txn_id; } ;
typedef  TYPE_2__ id_private_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id_vtable ; 
 char* svn_cstring_tokenize (char*,char**) ; 

svn_fs_id_t *
svn_fs_base__id_parse(const char *data,
                      apr_size_t len,
                      apr_pool_t *pool)
{
  svn_fs_id_t *id;
  id_private_t *pvt;
  char *data_copy, *str;

  /* Dup the ID data into POOL.  Our returned ID will have references
     into this memory. */
  data_copy = apr_pstrmemdup(pool, data, len);

  /* Alloc a new svn_fs_id_t structure. */
  id = apr_palloc(pool, sizeof(*id));
  pvt = apr_palloc(pool, sizeof(*pvt));
  id->vtable = &id_vtable;
  id->fsap_data = pvt;

  /* Now, we basically just need to "split" this data on `.'
     characters.  We will use svn_cstring_tokenize, which will put
     terminators where each of the '.'s used to be.  Then our new
     id field will reference string locations inside our duplicate
     string.*/

  /* Node Id */
  str = svn_cstring_tokenize(".", &data_copy);
  if (str == NULL)
    return NULL;
  pvt->node_id = str;

  /* Copy Id */
  str = svn_cstring_tokenize(".", &data_copy);
  if (str == NULL)
    return NULL;
  pvt->copy_id = str;

  /* Txn Id */
  str = svn_cstring_tokenize(".", &data_copy);
  if (str == NULL)
    return NULL;
  pvt->txn_id = str;

  return id;
}