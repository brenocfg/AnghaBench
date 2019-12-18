#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_10__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_11__ {int out_of_date; scalar_t__ txn_filesize; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ extract_dir_entry_baton_t ;
struct TYPE_12__ {scalar_t__ txn_filesize; int /*<<< orphan*/  count; int /*<<< orphan*/  lengths; int /*<<< orphan*/  entries; } ;
typedef  TYPE_3__ dir_data_t ;
typedef  size_t apr_uint32_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_1__ const*,size_t) ; 
 size_t find_entry (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_deserialize (TYPE_1__*,int /*<<< orphan*/ **) ; 
 void* svn_temp_deserializer__ptr (TYPE_1__ const* const*,void const* const*) ; 
 int /*<<< orphan*/  svn_temp_deserializer__resolve (TYPE_1__*,void**) ; 

svn_error_t *
svn_fs_fs__extract_dir_entry(void **out,
                             const void *data,
                             apr_size_t data_len,
                             void *baton,
                             apr_pool_t *pool)
{
  const dir_data_t *dir_data = data;
  extract_dir_entry_baton_t *entry_baton = baton;
  svn_boolean_t found;

  /* resolve the reference to the entries array */
  const svn_fs_dirent_t * const *entries =
    svn_temp_deserializer__ptr(data, (const void *const *)&dir_data->entries);

  /* resolve the reference to the lengths array */
  const apr_uint32_t *lengths =
    svn_temp_deserializer__ptr(data, (const void *const *)&dir_data->lengths);

  /* binary search for the desired entry by name */
  apr_size_t pos = find_entry((svn_fs_dirent_t **)entries,
                              entry_baton->name,
                              dir_data->count,
                              &found);

  /* de-serialize that entry or return NULL, if no match has been found.
   * Be sure to check that the directory contents is still up-to-date. */
  entry_baton->out_of_date
    = dir_data->txn_filesize != entry_baton->txn_filesize;

  *out = NULL;
  if (found && !entry_baton->out_of_date)
    {
      const svn_fs_dirent_t *source =
          svn_temp_deserializer__ptr(entries, (const void *const *)&entries[pos]);

      /* Entries have been serialized one-by-one, each time including all
       * nested structures and strings. Therefore, they occupy a single
       * block of memory whose end-offset is either the beginning of the
       * next entry or the end of the buffer
       */
      apr_size_t size = lengths[pos];

      /* copy & deserialize the entry */
      svn_fs_dirent_t *new_entry = apr_pmemdup(pool, source, size);

      svn_temp_deserializer__resolve(new_entry, (void **)&new_entry->name);
      svn_fs_fs__id_deserialize(new_entry, (svn_fs_id_t **)&new_entry->id);
      *(svn_fs_dirent_t **)out = new_entry;
    }

  return SVN_NO_ERROR;
}