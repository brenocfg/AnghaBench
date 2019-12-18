#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ ino; } ;

/* Variables and functions */
 TYPE_1__ curfile ; 
 char* extbuf ; 
 int extbufsize ; 
 scalar_t__ extloc ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static char *
setupextattr(int extsize)
{

	extloc = 0;
	if (extsize <= extbufsize)
		return (extbuf);
	if (extbufsize > 0)
		free(extbuf);
	if ((extbuf = malloc(extsize)) != NULL) {
		extbufsize = extsize;
		return (extbuf);
	}
	extbufsize = 0;
	extbuf = NULL;
	fprintf(stderr, "Cannot extract %d bytes %s for inode %ju, name %s\n",
	    extsize, "of extended attributes", (uintmax_t)curfile.ino,
	    curfile.name);
	return (NULL);
}