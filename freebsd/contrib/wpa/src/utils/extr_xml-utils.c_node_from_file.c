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
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memset (char*,char,int) ; 
 char* os_readfile (char const*,size_t*) ; 
 char* os_realloc (char*,size_t) ; 
 char* os_strstr (char*,char*) ; 
 int /*<<< orphan*/ * xml_node_from_buf (struct xml_node_ctx*,char*) ; 

xml_node_t * node_from_file(struct xml_node_ctx *ctx, const char *name)
{
	xml_node_t *node;
	char *buf, *buf2, *start;
	size_t len;

	buf = os_readfile(name, &len);
	if (buf == NULL)
		return NULL;
	buf2 = os_realloc(buf, len + 1);
	if (buf2 == NULL) {
		os_free(buf);
		return NULL;
	}
	buf = buf2;
	buf[len] = '\0';

	start = os_strstr(buf, "<!DOCTYPE ");
	if (start) {
		char *pos = start + 1;
		int count = 1;
		while (*pos) {
			if (*pos == '<')
				count++;
			else if (*pos == '>') {
				count--;
				if (count == 0) {
					pos++;
					break;
				}
			}
			pos++;
		}
		if (count == 0) {
			/* Remove DOCTYPE to allow the file to be parsed */
			os_memset(start, ' ', pos - start);
		}
	}

	node = xml_node_from_buf(ctx, buf);
	os_free(buf);

	return node;
}