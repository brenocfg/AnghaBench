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
struct str_buf {char* buf; void* warning; void* error; struct str_buf* userData; } ;
typedef  struct str_buf xmlValidCtxt ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDtdPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/  vctx ;
struct xml_node_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  errors ;

/* Variables and functions */
 void* add_str ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memset (struct str_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xmlDocCopyNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlDocSetRootElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDtd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlNewDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlParseDTD (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int xmlValidateDtd (struct str_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int xml_validate_dtd(struct xml_node_ctx *ctx, xml_node_t *node,
		     const char *dtd_fname, char **ret_err)
{
	xmlDocPtr doc;
	xmlNodePtr n;
	xmlValidCtxt vctx;
	xmlDtdPtr dtd;
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

	dtd = xmlParseDTD(NULL, (const xmlChar *) dtd_fname);
	if (dtd == NULL) {
		xmlFreeDoc(doc);
		return -1;
	}

	os_memset(&vctx, 0, sizeof(vctx));
	vctx.userData = &errors;
	vctx.error = add_str;
	vctx.warning = add_str;
	ret = xmlValidateDtd(&vctx, doc, dtd);
	xmlFreeDoc(doc);
	xmlFreeDtd(dtd);

	if (ret == 1) {
		os_free(errors.buf);
		return 0;
	} else {
		if (ret_err)
			*ret_err = errors.buf;
		else
			os_free(errors.buf);
		return -1;
	}
}