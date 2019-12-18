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
struct mt_status_data {int /*<<< orphan*/  entries; } ;
typedef  int /*<<< orphan*/ * XML_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int XML_Parse (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * XML_ParserCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XML_ParserFree (int /*<<< orphan*/ *) ; 
 int XML_STATUS_ERROR ; 
 int /*<<< orphan*/  XML_SetCharacterDataHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetElementHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetUserData (int /*<<< orphan*/ *,struct mt_status_data*) ; 
 int /*<<< orphan*/  bzero (struct mt_status_data*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mt_char_handler ; 
 int /*<<< orphan*/  mt_end_element ; 
 int /*<<< orphan*/  mt_start_element ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
mt_get_status(char *xml_str, struct mt_status_data *status_data)
{
	XML_Parser parser;
	int retval;

	bzero(status_data, sizeof(*status_data));
	STAILQ_INIT(&status_data->entries);

	parser = XML_ParserCreate(NULL);
	if (parser == NULL) {
		errno = ENOMEM;
		return (XML_STATUS_ERROR);
	}

	XML_SetUserData(parser, status_data);
	XML_SetElementHandler(parser, mt_start_element, mt_end_element);
	XML_SetCharacterDataHandler(parser, mt_char_handler);

	retval = XML_Parse(parser, xml_str, strlen(xml_str), 1);
	XML_ParserFree(parser);
	return (retval);
}