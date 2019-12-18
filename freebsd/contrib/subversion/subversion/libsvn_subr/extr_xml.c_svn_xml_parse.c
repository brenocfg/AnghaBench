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
struct TYPE_4__ {int /*<<< orphan*/  parser; int /*<<< orphan*/ * error; } ;
typedef  TYPE_1__ svn_xml_parser_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_XML_MALFORMED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  XML_ErrorString (int /*<<< orphan*/ ) ; 
 long XML_GetCurrentLineNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_GetErrorCode (int /*<<< orphan*/ ) ; 
 int XML_Parse (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  svn_xml_free_parser (TYPE_1__*) ; 

svn_error_t *
svn_xml_parse(svn_xml_parser_t *svn_parser,
              const char *buf,
              apr_size_t len,
              svn_boolean_t is_final)
{
  svn_error_t *err;
  int success;

  /* Parse some xml data */
  success = XML_Parse(svn_parser->parser, buf, (int) len, is_final);

  /* Did an error occur somewhere *inside* the expat callbacks? */
  if (svn_parser->error)
    {
      /* Kill all parsers and return the error */
      svn_xml_free_parser(svn_parser);
      return svn_parser->error;
    }

  /* If expat choked internally, return its error. */
  if (! success)
    {
      /* Line num is "int" in Expat v1, "long" in v2; hide the difference. */
      long line = XML_GetCurrentLineNumber(svn_parser->parser);

      err = svn_error_createf
        (SVN_ERR_XML_MALFORMED, NULL,
         _("Malformed XML: %s at line %ld"),
         XML_ErrorString(XML_GetErrorCode(svn_parser->parser)), line);

      /* Kill all parsers and return the expat error */
      svn_xml_free_parser(svn_parser);
      return err;
    }

  return SVN_NO_ERROR;
}