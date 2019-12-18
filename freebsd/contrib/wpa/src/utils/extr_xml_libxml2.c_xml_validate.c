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
typedef  int /*<<< orphan*/  xml_node_t ;
typedef  int /*<<< orphan*/  xmlSchemaValidityWarningFunc ;
typedef  int /*<<< orphan*/  xmlSchemaValidityErrorFunc ;
typedef  int /*<<< orphan*/  xmlSchemaValidCtxtPtr ;
typedef  int /*<<< orphan*/  xmlSchemaPtr ;
typedef  int /*<<< orphan*/  xmlSchemaParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct xml_node_ctx {int dummy; } ;
struct str_buf {char* buf; } ;
typedef  int /*<<< orphan*/  errors ;

/* Variables and functions */
 scalar_t__ add_str ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memset (struct str_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xmlDocCopyNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlDocSetRootElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlNewDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlSchemaFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlSchemaFreeParserCtxt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlSchemaFreeValidCtxt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlSchemaNewParserCtxt (char const*) ; 
 int /*<<< orphan*/  xmlSchemaNewValidCtxt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlSchemaParse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlSchemaSetParserErrors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct str_buf*) ; 
 int /*<<< orphan*/  xmlSchemaSetValidErrors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct str_buf*) ; 
 int xmlSchemaValidateDoc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int xml_validate(struct xml_node_ctx *ctx, xml_node_t *node,
		 const char *xml_schema_fname, char **ret_err)
{
	xmlDocPtr doc;
	xmlNodePtr n;
	xmlSchemaParserCtxtPtr pctx;
	xmlSchemaValidCtxtPtr vctx;
	xmlSchemaPtr schema;
	int ret;
	struct str_buf errors;

	if (ret_err)
		*ret_err = NULL;

	doc = xmlNewDoc((xmlChar *) "1.0");
	if (doc == NULL)
		return -1;
	n = xmlDocCopyNode((xmlNodePtr) node, doc, 1);
	if (n == NULL) {
		xmlFreeDoc(doc);
		return -1;
	}
	xmlDocSetRootElement(doc, n);

	os_memset(&errors, 0, sizeof(errors));

	pctx = xmlSchemaNewParserCtxt(xml_schema_fname);
	xmlSchemaSetParserErrors(pctx, (xmlSchemaValidityErrorFunc) add_str,
				 (xmlSchemaValidityWarningFunc) add_str,
				 &errors);
	schema = xmlSchemaParse(pctx);
	xmlSchemaFreeParserCtxt(pctx);

	vctx = xmlSchemaNewValidCtxt(schema);
	xmlSchemaSetValidErrors(vctx, (xmlSchemaValidityErrorFunc) add_str,
				(xmlSchemaValidityWarningFunc) add_str,
				&errors);

	ret = xmlSchemaValidateDoc(vctx, doc);
	xmlSchemaFreeValidCtxt(vctx);
	xmlFreeDoc(doc);
	xmlSchemaFree(schema);

	if (ret == 0) {
		os_free(errors.buf);
		return 0;
	} else if (ret > 0) {
		if (ret_err)
			*ret_err = errors.buf;
		else
			os_free(errors.buf);
		return -1;
	} else {
		if (ret_err)
			*ret_err = errors.buf;
		else
			os_free(errors.buf);
		return -1;
	}
}