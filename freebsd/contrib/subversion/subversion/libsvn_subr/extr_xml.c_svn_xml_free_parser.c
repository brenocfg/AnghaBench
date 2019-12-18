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
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_xml_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_pool_cleanup_run (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_cleanup ; 

void
svn_xml_free_parser(svn_xml_parser_t *svn_parser)
{
  apr_pool_cleanup_run(svn_parser->pool, svn_parser, parser_cleanup);
}