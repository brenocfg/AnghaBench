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
struct TYPE_2__ {int /*<<< orphan*/  parser; } ;
typedef  TYPE_1__ svn_xml_parser_t ;
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  XML_StopParser (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void expat_entity_declaration(void *userData,
                                     const XML_Char *entityName,
                                     int is_parameter_entity,
                                     const XML_Char *value,
                                     int value_length,
                                     const XML_Char *base,
                                     const XML_Char *systemId,
                                     const XML_Char *publicId,
                                     const XML_Char *notationName)
{
  svn_xml_parser_t *svn_parser = userData;

  /* Stop the parser if an entity declaration is hit. */
  XML_StopParser(svn_parser->parser, 0 /* resumable */);
}