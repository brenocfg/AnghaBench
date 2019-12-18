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
struct httpread {char* hdr; } ;

/* Variables and functions */
 char* os_strchr (char*,char) ; 
 int os_strlen (char const*) ; 
 int /*<<< orphan*/  os_strncasecmp (char*,char const*,int) ; 

char * httpread_hdr_line_get(struct httpread *h, const char *tag)
{
	int tag_len = os_strlen(tag);
	char *hdr = h->hdr;
	hdr = os_strchr(hdr, '\n');
	if (hdr == NULL)
		return NULL;
	hdr++;
	for (;;) {
		if (!os_strncasecmp(hdr, tag, tag_len)) {
			hdr += tag_len;
			while (*hdr == ' ' || *hdr == '\t')
				hdr++;
			return hdr;
		}
		hdr = os_strchr(hdr, '\n');
		if (hdr == NULL)
			return NULL;
		hdr++;
	}
}