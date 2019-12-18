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

/* Variables and functions */
 int /*<<< orphan*/ * _getcwd (char*,int) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void Q_getwd (char *out)
{
	int i = 0;

#ifdef WIN32
   if (_getcwd (out, 256) == NULL)
     strcpy(out, ".");  /* shrug */
   strcat (out, "\\");
#else
   if (getcwd (out, 256) == NULL)
     strcpy(out, ".");  /* shrug */
   strcat (out, "/");
#endif

   while ( out[i] != 0 )
   {
	   if ( out[i] == '\\' )
		   out[i] = '/';
	   i++;
   }
}