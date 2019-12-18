#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* magic; } ;
typedef  TYPE_1__ svn_magic__cookie_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int MAGIC_ERROR ; 
 int MAGIC_MIME ; 
 int MAGIC_MIME_TYPE ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_ENABLE_MAGIC_FILE ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_MISCELLANY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_magic_cookie ; 
 int /*<<< orphan*/  magic_close (void*) ; 
 int magic_load (void*,int /*<<< orphan*/ *) ; 
 void* magic_open (int) ; 
 int /*<<< orphan*/  svn_config_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_magic__init(svn_magic__cookie_t **magic_cookie,
                apr_hash_t *config,
                apr_pool_t *result_pool)
{
  svn_magic__cookie_t *mc = NULL;

#ifdef SVN_HAVE_LIBMAGIC
  if (config)
    {
      svn_boolean_t enable;
      svn_config_t *cfg = svn_hash_gets(config, SVN_CONFIG_CATEGORY_CONFIG);

      SVN_ERR(svn_config_get_bool(cfg, &enable,
                                  SVN_CONFIG_SECTION_MISCELLANY,
                                  SVN_CONFIG_OPTION_ENABLE_MAGIC_FILE,
                                  TRUE));
      if (!enable)
        {
          *magic_cookie = NULL;
          return SVN_NO_ERROR;
        }
    }

  mc = apr_palloc(result_pool, sizeof(*mc));

  /* Initialise libmagic. */
#ifndef MAGIC_MIME_TYPE
  /* Some old versions of libmagic don't support MAGIC_MIME_TYPE.
   * We can use MAGIC_MIME instead. It returns more than we need
   * but we can work around that (see below). */
  mc->magic = magic_open(MAGIC_MIME | MAGIC_ERROR);
#else
  mc->magic = magic_open(MAGIC_MIME_TYPE | MAGIC_ERROR);
#endif
  if (mc->magic)
    {
      /* This loads the default magic database.
       * Point the MAGIC environment variable at your favourite .mgc
       * file to load a non-default database. */
      if (magic_load(mc->magic, NULL) == -1)
        {
          magic_close(mc->magic);
          mc = NULL;
        }
      else
        apr_pool_cleanup_register(result_pool, mc, close_magic_cookie,
                                  apr_pool_cleanup_null);
    }
#endif

  *magic_cookie = mc;

  return SVN_NO_ERROR;
}