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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
struct TYPE_3__ {scalar_t__ format; int max_deltification_walk; int max_linear_deltification; int revprop_pack_size; int block_size; int l2p_page_size; int p2l_page_size; scalar_t__ delta_compression_type; void* fail_stop; int /*<<< orphan*/  memcache; void* verify_before_commit; void* delta_compression_level; void* pack_after_commit; void* compress_packed_revprops; void* deltify_properties; void* deltify_directories; void* rep_sharing_allowed; } ;
typedef  TYPE_1__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OPTION_BLOCK_SIZE ; 
 int /*<<< orphan*/  CONFIG_OPTION_COMPRESSION ; 
 int /*<<< orphan*/  CONFIG_OPTION_COMPRESSION_LEVEL ; 
 int /*<<< orphan*/  CONFIG_OPTION_COMPRESS_PACKED_REVPROPS ; 
 int /*<<< orphan*/  CONFIG_OPTION_ENABLE_DIR_DELTIFICATION ; 
 int /*<<< orphan*/  CONFIG_OPTION_ENABLE_PROPS_DELTIFICATION ; 
 int /*<<< orphan*/  CONFIG_OPTION_ENABLE_REP_SHARING ; 
 int /*<<< orphan*/  CONFIG_OPTION_FAIL_STOP ; 
 int /*<<< orphan*/  CONFIG_OPTION_L2P_PAGE_SIZE ; 
 int /*<<< orphan*/  CONFIG_OPTION_MAX_DELTIFICATION_WALK ; 
 int /*<<< orphan*/  CONFIG_OPTION_MAX_LINEAR_DELTIFICATION ; 
 int /*<<< orphan*/  CONFIG_OPTION_P2L_PAGE_SIZE ; 
 int /*<<< orphan*/  CONFIG_OPTION_PACK_AFTER_COMMIT ; 
 int /*<<< orphan*/  CONFIG_OPTION_REVPROP_PACK_SIZE ; 
 int /*<<< orphan*/  CONFIG_OPTION_VERIFY_BEFORE_COMMIT ; 
 int /*<<< orphan*/  CONFIG_SECTION_CACHES ; 
 int /*<<< orphan*/  CONFIG_SECTION_DEBUG ; 
 int /*<<< orphan*/  CONFIG_SECTION_DELTIFICATION ; 
 int /*<<< orphan*/  CONFIG_SECTION_IO ; 
 int /*<<< orphan*/  CONFIG_SECTION_PACKED_REVPROPS ; 
 int /*<<< orphan*/  CONFIG_SECTION_REP_SHARING ; 
 void* FALSE ; 
 int /*<<< orphan*/  MAX (void*,void*) ; 
 void* MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH_CONFIG ; 
 void* SVN_DELTA_COMPRESSION_LEVEL_DEFAULT ; 
 int /*<<< orphan*/  SVN_DELTA_COMPRESSION_LEVEL_MAX ; 
 void* SVN_DELTA_COMPRESSION_LEVEL_NONE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CONFIG_VALUE ; 
 int SVN_FS_FS_MAX_DELTIFICATION_WALK ; 
 int SVN_FS_FS_MAX_LINEAR_DELTIFICATION ; 
 scalar_t__ SVN_FS_FS__MIN_DELTIFICATION_FORMAT ; 
 scalar_t__ SVN_FS_FS__MIN_LOG_ADDRESSING_FORMAT ; 
 scalar_t__ SVN_FS_FS__MIN_PACKED_FORMAT ; 
 scalar_t__ SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT ; 
 scalar_t__ SVN_FS_FS__MIN_REP_SHARING_FORMAT ; 
 scalar_t__ SVN_FS_FS__MIN_SVNDIFF1_FORMAT ; 
 scalar_t__ SVN_FS_FS__MIN_SVNDIFF2_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ compression_type_lz4 ; 
 scalar_t__ compression_type_none ; 
 void* compression_type_zlib ; 
 int /*<<< orphan*/  parse_compression_option (scalar_t__*,void**,char const*) ; 
 int /*<<< orphan*/  svn_cache__make_memcache_from_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_get_bool (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  svn_config_get_int64 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_config_read3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,void*,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cstring_atoi (void**,char const*) ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_block_size (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_config(fs_fs_data_t *ffd,
            const char *fs_path,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  svn_config_t *config;

  SVN_ERR(svn_config_read3(&config,
                           svn_dirent_join(fs_path, PATH_CONFIG, scratch_pool),
                           FALSE, FALSE, FALSE, scratch_pool));

  /* Initialize ffd->rep_sharing_allowed. */
  if (ffd->format >= SVN_FS_FS__MIN_REP_SHARING_FORMAT)
    SVN_ERR(svn_config_get_bool(config, &ffd->rep_sharing_allowed,
                                CONFIG_SECTION_REP_SHARING,
                                CONFIG_OPTION_ENABLE_REP_SHARING, TRUE));
  else
    ffd->rep_sharing_allowed = FALSE;

  /* Initialize deltification settings in ffd. */
  if (ffd->format >= SVN_FS_FS__MIN_DELTIFICATION_FORMAT)
    {
      SVN_ERR(svn_config_get_bool(config, &ffd->deltify_directories,
                                  CONFIG_SECTION_DELTIFICATION,
                                  CONFIG_OPTION_ENABLE_DIR_DELTIFICATION,
                                  TRUE));
      SVN_ERR(svn_config_get_bool(config, &ffd->deltify_properties,
                                  CONFIG_SECTION_DELTIFICATION,
                                  CONFIG_OPTION_ENABLE_PROPS_DELTIFICATION,
                                  TRUE));
      SVN_ERR(svn_config_get_int64(config, &ffd->max_deltification_walk,
                                   CONFIG_SECTION_DELTIFICATION,
                                   CONFIG_OPTION_MAX_DELTIFICATION_WALK,
                                   SVN_FS_FS_MAX_DELTIFICATION_WALK));
      SVN_ERR(svn_config_get_int64(config, &ffd->max_linear_deltification,
                                   CONFIG_SECTION_DELTIFICATION,
                                   CONFIG_OPTION_MAX_LINEAR_DELTIFICATION,
                                   SVN_FS_FS_MAX_LINEAR_DELTIFICATION));
    }
  else
    {
      ffd->deltify_directories = FALSE;
      ffd->deltify_properties = FALSE;
      ffd->max_deltification_walk = SVN_FS_FS_MAX_DELTIFICATION_WALK;
      ffd->max_linear_deltification = SVN_FS_FS_MAX_LINEAR_DELTIFICATION;
    }

  /* Initialize revprop packing settings in ffd. */
  if (ffd->format >= SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT)
    {
      SVN_ERR(svn_config_get_bool(config, &ffd->compress_packed_revprops,
                                  CONFIG_SECTION_PACKED_REVPROPS,
                                  CONFIG_OPTION_COMPRESS_PACKED_REVPROPS,
                                  FALSE));
      SVN_ERR(svn_config_get_int64(config, &ffd->revprop_pack_size,
                                   CONFIG_SECTION_PACKED_REVPROPS,
                                   CONFIG_OPTION_REVPROP_PACK_SIZE,
                                   ffd->compress_packed_revprops
                                       ? 0x40
                                       : 0x10));

      ffd->revprop_pack_size *= 1024;
    }
  else
    {
      ffd->revprop_pack_size = 0x10000;
      ffd->compress_packed_revprops = FALSE;
    }

  if (ffd->format >= SVN_FS_FS__MIN_LOG_ADDRESSING_FORMAT)
    {
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
    }
  else
    {
      /* should be irrelevant but we initialize them anyway */
      ffd->block_size = 0x1000; /* Matches default APR file buffer size. */
      ffd->l2p_page_size = 0x2000;    /* Matches above default. */
      ffd->p2l_page_size = 0x100000;  /* Matches above default in bytes. */
    }

  if (ffd->format >= SVN_FS_FS__MIN_PACKED_FORMAT)
    {
      SVN_ERR(svn_config_get_bool(config, &ffd->pack_after_commit,
                                  CONFIG_SECTION_DEBUG,
                                  CONFIG_OPTION_PACK_AFTER_COMMIT,
                                  FALSE));
    }
  else
    {
      ffd->pack_after_commit = FALSE;
    }

  /* Initialize compression settings in ffd. */
  if (ffd->format >= SVN_FS_FS__MIN_DELTIFICATION_FORMAT)
    {
      const char *compression_val;
      const char *compression_level_val;

      svn_config_get(config, &compression_val,
                     CONFIG_SECTION_DELTIFICATION,
                     CONFIG_OPTION_COMPRESSION, NULL);
      svn_config_get(config, &compression_level_val,
                     CONFIG_SECTION_DELTIFICATION,
                     CONFIG_OPTION_COMPRESSION_LEVEL, NULL);
      if (compression_val && compression_level_val)
        {
          return svn_error_create(SVN_ERR_BAD_CONFIG_VALUE, NULL,
                                  _("The 'compression' and 'compression-level' "
                                    "config options are mutually exclusive"));
        }
      else if (compression_val)
        {
          SVN_ERR(parse_compression_option(&ffd->delta_compression_type,
                                           &ffd->delta_compression_level,
                                           compression_val));
          if (ffd->delta_compression_type == compression_type_lz4 &&
              ffd->format < SVN_FS_FS__MIN_SVNDIFF2_FORMAT)
            {
              return svn_error_create(SVN_ERR_BAD_CONFIG_VALUE, NULL,
                                      _("Compression type 'lz4' requires "
                                        "filesystem format 8 or higher"));
            }
        }
      else if (compression_level_val)
        {
          /* Handle the deprecated 'compression-level' option. */
          ffd->delta_compression_type = compression_type_zlib;
          SVN_ERR(svn_cstring_atoi(&ffd->delta_compression_level,
                                   compression_level_val));
          ffd->delta_compression_level =
            MIN(MAX(SVN_DELTA_COMPRESSION_LEVEL_NONE,
                    ffd->delta_compression_level),
                SVN_DELTA_COMPRESSION_LEVEL_MAX);
        }
      else
        {
          /* Nothing specified explicitly, use the default settings:
           * LZ4 compression for formats supporting it and zlib otherwise. */
          if (ffd->format >= SVN_FS_FS__MIN_SVNDIFF2_FORMAT)
            ffd->delta_compression_type = compression_type_lz4;
          else
            ffd->delta_compression_type = compression_type_zlib;

          ffd->delta_compression_level = SVN_DELTA_COMPRESSION_LEVEL_DEFAULT;
        }
    }
  else if (ffd->format >= SVN_FS_FS__MIN_SVNDIFF1_FORMAT)
    {
      ffd->delta_compression_type = compression_type_zlib;
      ffd->delta_compression_level = SVN_DELTA_COMPRESSION_LEVEL_DEFAULT;
    }
  else
    {
      ffd->delta_compression_type = compression_type_none;
      ffd->delta_compression_level = SVN_DELTA_COMPRESSION_LEVEL_NONE;
    }

#ifdef SVN_DEBUG
  SVN_ERR(svn_config_get_bool(config, &ffd->verify_before_commit,
                              CONFIG_SECTION_DEBUG,
                              CONFIG_OPTION_VERIFY_BEFORE_COMMIT,
                              TRUE));
#else
  SVN_ERR(svn_config_get_bool(config, &ffd->verify_before_commit,
                              CONFIG_SECTION_DEBUG,
                              CONFIG_OPTION_VERIFY_BEFORE_COMMIT,
                              FALSE));
#endif

  /* memcached configuration */
  SVN_ERR(svn_cache__make_memcache_from_config(&ffd->memcache, config,
                                               result_pool, scratch_pool));

  SVN_ERR(svn_config_get_bool(config, &ffd->fail_stop,
                              CONFIG_SECTION_CACHES, CONFIG_OPTION_FAIL_STOP,
                              FALSE));

  return SVN_NO_ERROR;
}