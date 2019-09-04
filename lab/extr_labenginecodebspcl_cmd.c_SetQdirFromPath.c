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
typedef  int /*<<< orphan*/  temp ;

/* Variables and functions */
 char* BASEDIRNAME ; 
 int /*<<< orphan*/  Error (char*,char*,...) ; 
 int /*<<< orphan*/  Q_getwd (char*,int) ; 
 int /*<<< orphan*/  Q_strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  gamedir ; 
 int /*<<< orphan*/  qdir ; 
 int /*<<< orphan*/  qprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

void SetQdirFromPath (char *path)
{
	char	temp[1024];
	char	*c;
	int		len;

	if (!(path[0] == '/' || path[0] == '\\' || path[1] == ':'))
	{	// path is partial
		Q_getwd (temp, sizeof(temp));
		strcat (temp, path);
		path = temp;
	}

	// search for "quake2" in path

	len = strlen(BASEDIRNAME);
	for (c=path+strlen(path)-1 ; c != path ; c--)
		if (!Q_strncasecmp (c, BASEDIRNAME, len))
		{
			strncpy (qdir, path, c+len+1-path);
			qprintf ("qdir: %s\n", qdir);
			c += len+1;
			while (*c)
			{
				if (*c == '/' || *c == '\\')
				{
					strncpy (gamedir, path, c+1-path);
					qprintf ("gamedir: %s\n", gamedir);
					return;
				}
				c++;
			}
			Error ("No gamedir in %s", path);
			return;
		}
	Error ("SetQdirFromPath: no '%s' in %s", BASEDIRNAME, path);
}