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
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 unsigned char* base64_decode (unsigned char*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* xml_node_get_text (struct xml_node_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (struct xml_node_ctx*,char*) ; 

char * xml_node_get_base64_text(struct xml_node_ctx *ctx, xml_node_t *node,
				int *ret_len)
{
	char *txt;
	unsigned char *ret;
	size_t len;

	txt = xml_node_get_text(ctx, node);
	if (txt == NULL)
		return NULL;

	ret = base64_decode((unsigned char *) txt, strlen(txt), &len);
	if (ret_len)
		*ret_len = len;
	xml_node_get_text_free(ctx, txt);
	if (ret == NULL)
		return NULL;
	txt = os_malloc(len + 1);
	if (txt == NULL) {
		os_free(ret);
		return NULL;
	}
	os_memcpy(txt, ret, len);
	txt[len] = '\0';
	return txt;
}