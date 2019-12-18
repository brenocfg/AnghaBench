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
struct TYPE_4__ {char const* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  token; int /*<<< orphan*/  pool; int /*<<< orphan*/  conn; int /*<<< orphan*/  eb; } ;
typedef  TYPE_2__ ra_svn_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_for_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_ra_svn__write_cmd_textdelta_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *ra_svn_svndiff_handler(void *baton, const char *data,
                                           apr_size_t *len)
{
  ra_svn_baton_t *b = baton;
  svn_string_t str;

  SVN_ERR(check_for_error(b->eb, b->pool));
  str.data = data;
  str.len = *len;
  return svn_ra_svn__write_cmd_textdelta_chunk(b->conn, b->pool,
                                               b->token, &str);
}