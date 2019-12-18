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
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 char* os_strdup (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  xmlDocCopyNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmlDocDumpFormatMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlDocSetRootElement (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewDoc (int /*<<< orphan*/ *) ; 

char * xml_node_to_str(struct xml_node_ctx *ctx, xml_node_t *node)
{
	xmlChar *buf;
	int bufsiz;
	char *ret, *pos;
	xmlNodePtr n = (xmlNodePtr) node;
	xmlDocPtr doc;

	doc = xmlNewDoc((xmlChar *) "1.0");
	n = xmlDocCopyNode(n, doc, 1);
	xmlDocSetRootElement(doc, n);
	xmlDocDumpFormatMemory(doc, &buf, &bufsiz, 0);
	xmlFreeDoc(doc);
	if (!buf)
		return NULL;
	pos = (char *) buf;
	if (strncmp(pos, "<?xml", 5) == 0) {
		pos = strchr(pos, '>');
		if (pos)
			pos++;
		while (pos && (*pos == '\r' || *pos == '\n'))
			pos++;
	}
	if (pos)
		ret = os_strdup(pos);
	else
		ret = NULL;
	xmlFree(buf);

	if (ret) {
		pos = ret;
		if (pos[0]) {
			while (pos[1])
				pos++;
		}
		while (pos >= ret && *pos == '\n')
			*pos-- = '\0';
	}

	return ret;
}