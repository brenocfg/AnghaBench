#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ config_access_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_config__write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_read3 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_generic_config(svn_stream_t **stream,
                   svn_checksum_t **checksum,
                   config_access_t *access,
                   const char *path,
                   svn_boolean_t must_exist,
                   apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *contents = svn_stringbuf_create_empty(access->pool);
  svn_config_t *config;

  /* Read the configuration and serialize it into CONTENTS.
   * That copy can then be processed by the authz parser etc. */
  SVN_ERR(svn_config_read3(&config, path, must_exist, TRUE, TRUE,
                           scratch_pool));
  SVN_ERR(svn_config__write(svn_stream_from_stringbuf(contents, scratch_pool),
                            config, scratch_pool));

  /* calculate MD5 over the whole file contents */
  SVN_ERR(svn_checksum(checksum, svn_checksum_md5,
                       contents->data, contents->len, access->pool));
  *stream = svn_stream_from_stringbuf(contents, access->pool);

  return SVN_NO_ERROR;
}