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
typedef  int /*<<< orphan*/  svn_xml_parser_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct entries_accumulator {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/ * parser; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * entries; } ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_start_tag ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_free_parser (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_xml_make_parser (struct entries_accumulator*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
parse_entries_xml(const char *dir_abspath,
                  apr_hash_t *entries,
                  const char *buf,
                  apr_size_t size,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_xml_parser_t *svn_parser;
  struct entries_accumulator accum;

  /* Set up userData for the XML parser. */
  accum.entries = entries;
  accum.pool = result_pool;
  accum.scratch_pool = svn_pool_create(scratch_pool);

  /* Create the XML parser */
  svn_parser = svn_xml_make_parser(&accum,
                                   handle_start_tag,
                                   NULL,
                                   NULL,
                                   scratch_pool);

  /* Store parser in its own userdata, so callbacks can call
     svn_xml_signal_bailout() */
  accum.parser = svn_parser;

  /* Parse. */
  SVN_ERR_W(svn_xml_parse(svn_parser, buf, size, TRUE),
            apr_psprintf(scratch_pool,
                         _("XML parser failed in '%s'"),
                         svn_dirent_local_style(dir_abspath, scratch_pool)));

  svn_pool_destroy(accum.scratch_pool);

  /* Clean up the XML parser */
  svn_xml_free_parser(svn_parser);

  return SVN_NO_ERROR;
}