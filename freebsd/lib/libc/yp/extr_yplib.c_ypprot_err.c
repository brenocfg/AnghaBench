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
 int YPERR_BADARGS ; 
 int YPERR_BADDB ; 
 int YPERR_DOMAIN ; 
 int YPERR_KEY ; 
 int YPERR_MAP ; 
 int YPERR_NOMORE ; 
 int YPERR_VERS ; 
 int YPERR_YPBIND ; 
 int YPERR_YPERR ; 
#define  YP_BADARGS 138 
#define  YP_BADDB 137 
#define  YP_BADOP 136 
#define  YP_FALSE 135 
#define  YP_NODOM 134 
#define  YP_NOKEY 133 
#define  YP_NOMAP 132 
#define  YP_NOMORE 131 
#define  YP_TRUE 130 
#define  YP_VERS 129 
#define  YP_YPERR 128 

int
ypprot_err(unsigned int incode)
{
	switch (incode) {
	case YP_TRUE:
		return (0);
	case YP_FALSE:
		return (YPERR_YPBIND);
	case YP_NOMORE:
		return (YPERR_NOMORE);
	case YP_NOMAP:
		return (YPERR_MAP);
	case YP_NODOM:
		return (YPERR_DOMAIN);
	case YP_NOKEY:
		return (YPERR_KEY);
	case YP_BADOP:
		return (YPERR_YPERR);
	case YP_BADDB:
		return (YPERR_BADDB);
	case YP_YPERR:
		return (YPERR_YPERR);
	case YP_BADARGS:
		return (YPERR_BADARGS);
	case YP_VERS:
		return (YPERR_VERS);
	}
	return (YPERR_YPERR);
}