#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct wrapped_receiver_baton_s {int /*<<< orphan*/  orig_baton; int /*<<< orphan*/ * (* orig_receiver ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,char) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wrapped_receiver(void *baton,
                 apr_int64_t line_no,
                 svn_revnum_t revision,
                 const char *author,
                 const char *date,
                 const char *line,
                 apr_pool_t *pool)
{
  struct wrapped_receiver_baton_s *b = baton;
  svn_stringbuf_t *expanded_line = svn_stringbuf_create(line, pool);

  svn_stringbuf_appendbyte(expanded_line, '\r');

  return b->orig_receiver(b->orig_baton, line_no, revision, author,
                          date, expanded_line->data, pool);
}