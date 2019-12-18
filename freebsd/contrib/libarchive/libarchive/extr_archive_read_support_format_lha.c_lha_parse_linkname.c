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
struct archive_string {char* s; void* length; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_strncpy (struct archive_string*,char*,size_t) ; 
 char* strchr (char*,char) ; 
 void* strlen (char*) ; 

__attribute__((used)) static int
lha_parse_linkname(struct archive_string *linkname,
    struct archive_string *pathname)
{
	char *	linkptr;
	size_t 	symlen;

	linkptr = strchr(pathname->s, '|');
	if (linkptr != NULL) {
		symlen = strlen(linkptr + 1);
		archive_strncpy(linkname, linkptr+1, symlen);

		*linkptr = 0;
		pathname->length = strlen(pathname->s);

		return (1);
	}
	return (0);
}