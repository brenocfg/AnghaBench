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
#define  YPBIND_ERR_ERR 130 
#define  YPBIND_ERR_NOSERV 129 
#define  YPBIND_ERR_RESC 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
ypbinderr_string(int incode)
{
	static char err[80];
	switch (incode) {
	case 0:
		return ("Success");
	case YPBIND_ERR_ERR:
		return ("Internal ypbind error");
	case YPBIND_ERR_NOSERV:
		return ("Domain not bound");
	case YPBIND_ERR_RESC:
		return ("System resource allocation failure");
	}
	sprintf(err, "Unknown ypbind error: #%d\n", incode);
	return (err);
}