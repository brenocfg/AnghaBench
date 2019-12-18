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
typedef  int /*<<< orphan*/  time_t ;
struct xml_data {void* ds; void* cdigest; void* cdigtype; void* czone; void* calgo; void* ctag; int /*<<< orphan*/  date; int /*<<< orphan*/  parser; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  XML_Parser ;

/* Variables and functions */
 void* BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 scalar_t__ BIO_write (void*,char*,int) ; 
 int /*<<< orphan*/  XML_SetCharacterDataHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetElementHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetEntityDeclHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetUserData (int /*<<< orphan*/ ,struct xml_data*) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xml_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ verb ; 
 int /*<<< orphan*/  xml_charhandle ; 
 int /*<<< orphan*/  xml_endelem ; 
 int /*<<< orphan*/  xml_entitydeclhandler ; 
 int /*<<< orphan*/  xml_startelem ; 

__attribute__((used)) static void
xml_parse_setup(XML_Parser parser, struct xml_data* data, time_t now)
{
	char buf[1024];
	memset(data, 0, sizeof(*data));
	XML_SetUserData(parser, data);
	data->parser = parser;
	data->date = now;
	data->ds = BIO_new(BIO_s_mem());
	data->ctag = BIO_new(BIO_s_mem());
	data->czone = BIO_new(BIO_s_mem());
	data->calgo = BIO_new(BIO_s_mem());
	data->cdigtype = BIO_new(BIO_s_mem());
	data->cdigest = BIO_new(BIO_s_mem());
	if(!data->ds || !data->ctag || !data->calgo || !data->czone ||
		!data->cdigtype || !data->cdigest) {
		if(verb) printf("out of memory\n");
		exit(0);
	}
	snprintf(buf, sizeof(buf), "; created by unbound-anchor on %s",
		ctime(&now));
	if(BIO_write(data->ds, buf, (int)strlen(buf)) < 0) {
		if(verb) printf("out of memory\n");
		exit(0);
	}
	XML_SetEntityDeclHandler(parser, xml_entitydeclhandler);
	XML_SetElementHandler(parser, xml_startelem, xml_endelem);
	XML_SetCharacterDataHandler(parser, xml_charhandle);
}