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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_create_unique_link (char const**,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_read_link (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_copy_link(const char *src,
                 const char *dst,
                 apr_pool_t *pool)

{
#ifdef HAVE_READLINK
  svn_string_t *link_dest;
  const char *dst_tmp;

  /* Notice what the link is pointing at... */
  SVN_ERR(svn_io_read_link(&link_dest, src, pool));

  /* Make a tmp-link pointing at the same thing. */
  SVN_ERR(svn_io_create_unique_link(&dst_tmp, dst, link_dest->data,
                                    ".tmp", pool));

  /* Move the tmp-link to link. */
  return svn_io_file_rename2(dst_tmp, dst, FALSE, pool);

#else
  return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                          _("Symbolic links are not supported on this "
                            "platform"));
#endif
}