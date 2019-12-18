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
struct mtextget {char* status_xml; size_t alloc_len; scalar_t__ status; } ;
typedef  int /*<<< orphan*/  extget ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ MT_EXT_GET_NEED_MORE_SPACE ; 
 scalar_t__ MT_EXT_GET_OK ; 
 int /*<<< orphan*/  bzero (struct mtextget*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl (int,unsigned long,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 

int
mt_get_xml_str(int mtfd, unsigned long cmd, char **xml_str)
{
	size_t alloc_len = 32768;
	struct mtextget extget;
	int error;

	*xml_str = NULL;

	for (;;) {
		bzero(&extget, sizeof(extget));
		*xml_str = malloc(alloc_len);
		if (*xml_str == NULL)
			return (-1);
		extget.status_xml = *xml_str;
		extget.alloc_len = alloc_len;

		error = ioctl(mtfd, cmd, (caddr_t)&extget);
		if (error == 0 && extget.status == MT_EXT_GET_OK)
			break;

		free(*xml_str);
		*xml_str = NULL;

		if (error != 0 || extget.status != MT_EXT_GET_NEED_MORE_SPACE)
			return (-1);

		/* The driver needs more space, so double and try again. */
		alloc_len *= 2;
	}
	return (0);
}