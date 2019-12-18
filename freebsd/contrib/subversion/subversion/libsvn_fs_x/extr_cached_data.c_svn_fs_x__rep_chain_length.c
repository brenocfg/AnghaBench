#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_revnum_t ;
struct TYPE_11__ {int /*<<< orphan*/  number; scalar_t__ change_set; } ;
struct TYPE_12__ {int /*<<< orphan*/  size; TYPE_1__ id; } ;
typedef  TYPE_2__ svn_fs_x__representation_t ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/  base_length; int /*<<< orphan*/  base_item_index; int /*<<< orphan*/  base_revision; } ;
typedef  TYPE_3__ svn_fs_x__rep_header_t ;
struct TYPE_14__ {int max_files_per_dir; } ;
typedef  TYPE_4__ svn_fs_x__data_t ;
struct TYPE_15__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_5__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  shared_file_t ;
typedef  int /*<<< orphan*/  rep_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  create_rep_state_body (int /*<<< orphan*/ **,TYPE_3__**,int /*<<< orphan*/ **,TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__change_set_by_rev (int /*<<< orphan*/ ) ; 
 int svn_fs_x__get_revnum (scalar_t__) ; 
 scalar_t__ svn_fs_x__rep_delta ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__rep_chain_length(int *chain_length,
                           int *shard_count,
                           svn_fs_x__representation_t *rep,
                           svn_fs_t *fs,
                           apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_revnum_t shard_size = ffd->max_files_per_dir;
  svn_boolean_t is_delta = FALSE;
  int count = 0;
  int shards = 1;
  svn_revnum_t revision = svn_fs_x__get_revnum(rep->id.change_set);
  svn_revnum_t last_shard = revision / shard_size;

  /* Note that this iteration pool will be used in a non-standard way.
   * To reuse open file handles between iterations (e.g. while within the
   * same pack file), we only clear this pool once in a while instead of
   * at the start of each iteration. */
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  /* Check whether the length of the deltification chain is acceptable.
   * Otherwise, shared reps may form a non-skipping delta chain in
   * extreme cases. */
  svn_fs_x__representation_t base_rep = *rep;

  /* re-use open files between iterations */
  shared_file_t *file_hint = NULL;

  svn_fs_x__rep_header_t *header;

  /* follow the delta chain towards the end but for at most
   * MAX_CHAIN_LENGTH steps. */
  do
    {
      rep_state_t *rep_state;
      revision = svn_fs_x__get_revnum(base_rep.id.change_set);
      if (revision / shard_size != last_shard)
        {
          last_shard = revision / shard_size;
          ++shards;
        }

      SVN_ERR(create_rep_state_body(&rep_state,
                                    &header,
                                    &file_hint,
                                    &base_rep,
                                    fs,
                                    iterpool,
                                    iterpool));

      base_rep.id.change_set
        = svn_fs_x__change_set_by_rev(header->base_revision);
      base_rep.id.number = header->base_item_index;
      base_rep.size = header->base_length;
      is_delta = header->type == svn_fs_x__rep_delta;

      /* Clear it the ITERPOOL once in a while.  Doing it too frequently
       * renders the FILE_HINT ineffective.  Doing too infrequently, may
       * leave us with too many open file handles.
       *
       * Note that this is mostly about efficiency, with larger values
       * being more efficient, and any non-zero value is legal here.  When
       * reading deltified contents, we may keep 10s of rev files open at
       * the same time and the system has to cope with that.  Thus, the
       * limit of 16 chosen below is in the same ballpark.
       */
      ++count;
      if (count % 16 == 0)
        {
          file_hint = NULL;
          svn_pool_clear(iterpool);
        }
    }
  while (is_delta && base_rep.id.change_set);

  *chain_length = count;
  *shard_count = shards;
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}