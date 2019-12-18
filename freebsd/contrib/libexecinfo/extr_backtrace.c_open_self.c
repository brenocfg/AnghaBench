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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
#define  CTL_KERN 130 
#define  KERN_PROC 129 
#define  KERN_PROC_PATHNAME 128 
 int MAXPATHLEN ; 
 char* SELF ; 
 int open (char const*,int) ; 
 int sysctl (int const*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
open_self(int flags)
{
	const char *pathname = SELF;
#ifdef KERN_PROC_PATHNAME
	static const int name[] = {
		CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1,
	};
	char path[MAXPATHLEN];
	size_t len;

	len = sizeof(path);
	if (sysctl(name, 4, path, &len, NULL, 0) != -1)
		pathname = path;
#endif
	return open(pathname, flags);
}