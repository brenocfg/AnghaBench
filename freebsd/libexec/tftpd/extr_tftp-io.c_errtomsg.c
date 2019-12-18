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
struct errmsg {int e_code; char const* e_msg; } ;
typedef  int /*<<< orphan*/  ebuf ;

/* Variables and functions */
 struct errmsg* errmsgs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
errtomsg(int error)
{
	static char ebuf[40];
	struct errmsg *pe;

	if (error == 0)
		return ("success");
	for (pe = errmsgs; pe->e_code >= 0; pe++)
		if (pe->e_code == error)
			return (pe->e_msg);
	snprintf(ebuf, sizeof(ebuf), "error %d", error);
	return (ebuf);
}