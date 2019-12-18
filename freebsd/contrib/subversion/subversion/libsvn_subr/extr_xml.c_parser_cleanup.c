#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * parser; } ;
typedef  TYPE_1__ svn_xml_parser_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  XML_ParserFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t parser_cleanup(void *data)
{
  svn_xml_parser_t *svn_parser = data;

  /* Free Expat parser. */
  if (svn_parser->parser)
    {
      XML_ParserFree(svn_parser->parser);
      svn_parser->parser = NULL;
    }
  return APR_SUCCESS;
}