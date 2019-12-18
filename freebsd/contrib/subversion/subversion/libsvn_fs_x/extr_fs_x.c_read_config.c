#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_deltification_walk; int max_linear_deltification; int delta_compression_level; int revprop_pack_size; int block_size; int l2p_page_size; int p2l_page_size; int /*<<< orphan*/  fail_stop; int /*<<< orphan*/  memcache; int /*<<< orphan*/  pack_after_commit; int /*<<< orphan*/  compress_packed_revprops; int /*<<< orphan*/  rep_sharing_allowed; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  int apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OPTION_BLOCK_SIZE ; 
 int /*<<< orphan*/  CONFIG_OPTION_COMPRESSION_LEVEL ; 
 int /*<<< orphan*/  CONFIG_OPTION_COMPRESS_PACKED_REVPROPS ; 
 int /*<<< orphan*/  CONFIG_OPTION_ENABLE_REP_SHARING ; 
 int /*<<< orphan*/  CONFIG_OPTION_FAIL_STOP ; 
 int /*<<< orphan*/  CONFIG_OPTION_L2P_PAGE_SIZE ; 
 int /*<<< orphan*/  CONFIG_OPTION_MAX_DELTIFICATION_WALK ; 
 int /*<<< orphan*/  CONFIG_OPTION_MAX_LINEAR_DELTIFICATION ; 
 int /*<<< orphan*/  CONFIG_OPTION_P2L_PAGE_SIZE ; 
 int /*<<< orphan*/  CONFIG_OPTION_PACK_AFTER_COMMIT ; 
 int /*<<< orphan*/  CONFIG_OPTION_REVPROP_PACK_SIZE ; 
 int /*<<< orphan*/  CONFIG_SECTION_CACHES ; 
 int /*<<< orphan*/  CONFIG_SECTION_DEBUG ; 
 int /*<<< orphan*/  CONFIG_SECTION_DELTIFICATION ; 
 int /*<<< orphan*/  CONFIG_SECTION_IO ; 
 int /*<<< orphan*/  CONFIG_SECTION_PACKED_REVPROPS ; 
 int /*<<< orphan*/  CONFIG_SECTION_REP_SHARING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH_CONFIG ; 
 int SVN_DELTA_COMPRESSION_LEVEL_DEFAULT ; 
 int /*<<< orphan*/  SVN_DELTA_COMPRESSION_LEVEL_MAX ; 
 int /*<<< orphan*/  SVN_DELTA_COMPRESSION_LEVEL_NONE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_X_MAX_DELTIFICATION_WALK ; 
 int SVN_FS_X_MAX_LINEAR_DELTIFICATION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_cache__make_memcache_from_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_config_get_int64 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_config_read3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_block_size (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_config(svn_fs_x__data_t *ffd,
            const char *fs_path,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  svn_config_t *config;
  apr_int64_t compression_level;

  SVN_ERR(svn_config_read3(&config,
                           svn_dirent_join(fs_path, PATH_CONFIG, scratch_pool),
                           FALSE, FALSE, FALSE, scratch_pool));

  /* Initialize ffd->rep_sharing_allowed. */
  SVN_ERR(svn_config_get_bool(config, &ffd->rep_sharing_allowed,
                              CONFIG_SECTION_REP_SHARING,
                              CONFIG_OPTION_ENABLE_REP_SHARING, TRUE));

  /* Initialize deltification settings in ffd. */
  SVN_ERR(svn_config_get_int64(config, &ffd->max_deltification_walk,
                               CONFIG_SECTION_DELTIFICATION,
                               CONFIG_OPTION_MAX_DELTIFICATION_WALK,
                               SVN_FS_X_MAX_DELTIFICATION_WALK));
  SVN_ERR(svn_config_get_int64(config, &ffd->max_linear_deltification,
                               CONFIG_SECTION_DELTIFICATION,
                               CONFIG_OPTION_MAX_LINEAR_DELTIFICATION,
                               SVN_FS_X_MAX_LINEAR_DELTIFICATION));
  SVN_ERR(svn_config_get_int64(config, &compression_level,
                               CONFIG_SECTION_DELTIFICATION,
                               CONFIG_OPTION_COMPRESSION_LEVEL,
                               SVN_DELTA_COMPRESSION_LEVEL_DEFAULT));
  ffd->delta_compression_level
    = (int)MIN(MAX(SVN_DELTA_COMPRESSION_LEVEL_NONE, compression_level),
                SVN_DELTA_COMPRESSION_LEVEL_MAX);

  /* Initialize revprop packing settings in ffd. */
  SVN_ERR(svn_config_get_bool(config, &ffd->compress_packed_revprops,
                              CONFIG_SECTION_PACKED_REVPROPS,
                              CONFIG_OPTION_COMPRESS_PACKED_REVPROPS,
                              TRUE));
  SVN_ERR(svn_config_get_int64(config, &ffd->revprop_pack_size,
                               CONFIG_SECTION_PACKED_REVPROPS,
                               CONFIG_OPTION_REVPROP_PACK_SIZE,
                               ffd->compress_packed_revprops
                                   ? 0x100
                                   : 0x40));

  ffd->revprop_pack_size *= 1024;

  /* I/O settings in ffd. */
  SVN_ERR(svn_config_get_int64(config, &ffd->block_size,
                               CONFIG_SECTION_IO,
                               CONFIG_OPTION_BLOCK_SIZE,
                               64));
  SVN_ERR(svn_config_get_int64(config, &ffd->l2p_page_size,
                               CONFIG_SECTION_IO,
                               CONFIG_OPTION_L2P_PAGE_SIZE,
                               0x2000));
  SVN_ERR(svn_config_get_int64(config, &ffd->p2l_page_size,
                               CONFIG_SECTION_IO,
                               CONFIG_OPTION_P2L_PAGE_SIZE,
                               0x400));

  /* Don't accept unreasonable or illegal values.
   * Block size and P2L page size are in kbytes;
   * L2P blocks are arrays of apr_off_t. */
  SVN_ERR(verify_block_size(ffd->block_size, 0x400,
                            CONFIG_OPTION_BLOCK_SIZE, scratch_pool));
  SVN_ERR(verify_block_size(ffd->p2l_page_size, 0x400,
                            CONFIG_OPTION_P2L_PAGE_SIZE, scratch_pool));
  SVN_ERR(verify_block_size(ffd->l2p_page_size, sizeof(apr_off_t),
                            CONFIG_OPTION_L2P_PAGE_SIZE, scratch_pool));

  /* convert kBytes to bytes */
  ffd->block_size *= 0x400;
  ffd->p2l_page_size *= 0x400;
  /* L2P pages are in entries - not in (k)Bytes */

  /* Debug options. */
  SVN_ERR(svn_config_get_bool(config, &ffd->pack_after_commit,
                              CONFIG_SECTION_DEBUG,
                              CONFIG_OPTION_PACK_AFTER_COMMIT,
                              FALSE));

  /* memcached configuration */
  SVN_ERR(svn_cache__make_memcache_from_config(&ffd->memcache, config,
                                               result_pool, scratch_pool));

  SVN_ERR(svn_config_get_bool(config, &ffd->fail_stop,
                              CONFIG_SECTION_CACHES, CONFIG_OPTION_FAIL_STOP,
                              FALSE));

  return SVN_NO_ERROR;
}